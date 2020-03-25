import re
import json
from typing import List, Dict, Tuple, Union
import sys


def substitute(string: str, templateName: str, arg: str) -> str:
    return re.sub('{{' + str(templateName) + '}}', arg, string)


def field_decl_list(fields: List[Tuple[str, str]]) -> str:
    decl_list = ''

    i = 0
    for f in fields:
        if i > 0:
            decl_list += '\n\n\t'
        decl_list += f'{f[0]} {f[1]};'
        i += 1

    return decl_list


def print_body(fields: List[Tuple[str, str]]) -> str:
    print_body = ''

    i = 0
    for f in fields:
        if i > 0:
            print_body += '\n\t\t'

        print_body += f'cout << '
        if i == 0:
            print_body += '"{" << '

        if i > 0:
            print_body += '", " << '

        print_body += f'{f[1]}'

        if i == len(fields) - 1:
            print_body += ' << "}"'

        print_body += ';'

        i += 1

    return print_body


def to_key_body(keyFields: List[str]) -> str:
    key_fields_init_list = '{'

    key_fields_init_list += ', '.join(keyFields)

    key_fields_init_list += '}'

    return key_fields_init_list


def equal_to_condition(fields: List[Tuple[str, str]]) -> str:
    if not fields:
        return 'true'
    return ' && '.join([f'lhs.{f[1]} == rhs.{f[1]}' for f in fields])


def hash_body(fields: List[Tuple[str, str]]) -> str:
    hash_body = ''
    i = 0

    for f in fields:

        if i > 0:
            hash_body += '\n\t\t\t'

        hash_body += f'boost::hash_combine(seed, p.{f[1]});'

        i += 1

    return hash_body

    # return '\n'.join([f'boost::hash_combine(seed, p.{f[1]})' for f in fields])


def children_conversion(qname: str, jsonpath: str, name: str, childrenInterAttr: Dict[str, List[str]]) -> str:
    lines = []

    with open(jsonpath + "QueryFields.json") as f:

        d = json.load(f)
        varsDict = d['varsDict']
        freevarsDict = d['freevarsDict']
        freekeyvarsDict = d['freekeyvarsDict']
        has_projection = {k: (varsDict[k] != freevarsDict[k]) for k in varsDict.keys()}

        for child in childrenInterAttr.keys():
            lines += [f'template<> {child}Key {name}Parcel::to<{child}Key>() const' + ' {']
            lines += ['\treturn {' + ', '.join(childrenInterAttr[child]) + '};']
            lines += ['}']

            if has_projection[child]:
                lines += [f"#ifdef PROJECTION_{qname}"]
                lines += [f'template<> PROJECTED_{child}Key {name}Parcel::to<PROJECTED_{child}Key>() const' + ' {']
                lines += ['\treturn {' + ', '.join(freekeyvarsDict[child]) + '};']
                lines += ['}\n']
                lines += ["#endif"]
            else:
                lines += [""]

        return "\n".join(lines)


# IMPORTANT: usecols should be sorted
def from_line_parsing_code(delim: str, usecols: List[int], fields: List[Tuple[str, str]],
                           conversionFuncs: Dict[str, str]) -> str:
    parsingCode = 'size_t pos;\n\n'
    lastCol = -1

    i = 0
    while i < len(usecols):
        if usecols[i] == lastCol + 1:
            parsingCode += f'\t\tpos = line.find("{delim}");\n'
            parsingCode += f'\t\t{fields[i][0]} {fields[i][1]} = {conversionFuncs[fields[i][0]]}(line.substr(0, pos));\n'
            parsingCode += f'\t\tline = line.substr(pos+1, string::npos);\n'
            parsingCode += '\n'

        else:
            parsingCode += f'\t\tfor(int _i = 0; _i < {usecols[i] - lastCol - 1}; _i++)' + ' {\n'
            parsingCode += f'\t\t\tpos = line.find("{delim}");\n\t\t\tline = line.substr(pos + 1, string::npos);\n'
            parsingCode += '\t\t}\n'
            parsingCode += f'\t\tpos = line.find("{delim}");\n'
            parsingCode += f'\t\t{fields[i][0]} {fields[i][1]} = {conversionFuncs[fields[i][0]]}(line.substr(0, pos));\n'

        lastCol = usecols[i]

        i += 1

    parsingCode += '\n\t\treturn {' + f'{", ".join([f[1] for f in fields])}' + '};'

    return parsingCode


def key_fields_decl_list(fields: List[Tuple[str, str]], keyFields: List[str]):
    key_fields_decl = ''

    fieldDict = {}

    for f in fields:
        fieldDict[f[1]] = f[0]

    i = 0
    for kf in keyFields:
        if i > 0:
            key_fields_decl += "\n\n\t"
        key_fields_decl += f'{fieldDict[kf]} {kf};'
        i += 1
    return key_fields_decl


def key_fields_print(keyFields: List[str]) -> str:
    if not keyFields:
        return 'cout << "{" << "}";'
    print_body = 'cout << "{" << ' + ' << '.join(keyFields) + ' << "}";'
    return print_body


def key_equal_to_condition(keyFields: List[str]) -> str:
    if not keyFields:
        return 'true'
    return ' && '.join([f'lhs.{f} == rhs.{f}' for f in keyFields])


def key_hash_body(keyFields: List[str]) -> str:
    hash_body = ''
    i = 0

    for f in keyFields:

        if i > 0:
            hash_body += '\n\t\t\t'

        hash_body += f'boost::hash_combine(seed, p.{f});'

        i += 1

    return hash_body


def child_includes(qname: str, childList: List[str], has_projection: Dict[str, bool]) -> str:
    proj_includes = [f'#include "PROJECTED_{child}Parcel.h"' for child in childList if has_projection[child]]
    includes = [f'#include "{child}Parcel.h"' for child in childList]
    return '\n'.join(includes + [f"#ifdef PROJECTION_{qname}"] + proj_includes + ["#endif"])


def create_parcel_file(qname: str, name: str, fields: List[Tuple[str, str]], keyFields: List[str],
                       childrenInterAttr: Dict[str, List[str]],
                       conversionFunctions: Dict[str, str], usecols: List[int], jsonpath: str, outputpath: str) -> None:
    # name = "C"
    outputFilename: str = name + "Parcel.h"
    # IMPORTANT: fields should be sorted according to position in the file (column order)
    # fields: List[Tuple[str, str]] = [('int', 'custKey')]
    # IMPORTANT: we assume that these fieldNames are in column order
    # keyFields: List[str] = ['custKey']
    # IMPORTANT: we assume that the fieldNames in each child are in the CHILD column order
    # childrenInterAttr: Dict[str, List[str]] = {}

    # conversionFunctions = {'int': 'stoi', 'long long': 'stoll', 'string': '', 'double': 'stod'}
    # IMPORTANT: usecols must be sorted
    # usecols: List[int] = [0]

    has_projection = json.load(open(jsonpath + "IndexParams.json"))["projection"]

    code = open('ParcelTemplate').read()
    code = substitute(code, 'name', name)
    code = substitute(code, 'fields', field_decl_list(fields))
    code = substitute(code, 'print_body', print_body(fields))
    code = substitute(code, 'key_fields_init_list', to_key_body(keyFields))
    code = substitute(code, 'equal_to_conditions', equal_to_condition(fields))
    code = substitute(code, 'hash_combine', hash_body(fields))
    code = substitute(code, 'child_conversion', children_conversion(qname, jsonpath, name, childrenInterAttr))
    code = substitute(code, 'from_body', from_line_parsing_code('|', usecols, fields, conversionFunctions))
    code = substitute(code, 'key_fields', key_fields_decl_list(fields, keyFields))
    code = substitute(code, 'key_print_body', key_fields_print(keyFields))
    code = substitute(code, 'key_hash_combine', key_hash_body(keyFields))
    code = substitute(code, 'key_equal_to_conditions', key_equal_to_condition(keyFields))
    code = substitute(code, 'child_includes', child_includes(qname, list(childrenInterAttr.keys()), has_projection))
    code = code.replace('\t', 4 * ' ')
    code = code.replace(f"{name}Parcel", f"{qname}_{name}Parcel")
    code = code.replace(f"{name}Key", f"{qname}_{name}Key")
    code = code.replace(f"{name}PARCEL", f"{qname}_{name}PARCEL")
    code = code.replace(f"{name}Table", f"{qname}_{name}Table")
    code = code.replace(f"{name}SplitTable", f"{qname}_{name}SplitTable")

    for c in list(childrenInterAttr.keys()):
        code = code.replace(f"{c}Parcel", f"{qname}_{c}Parcel")
        code = code.replace(f"{c}Key", f"{qname}_{c}Key")

    open(outputpath + qname + "_" + outputFilename, 'w+').write(code)


def generate_parcels_from_json(qname: str, jsonpath: str, outputpath: str) -> None:
    with open(jsonpath + 'ParcelCreateList.json') as f:
        dArray = json.load(f)['array']

        for d in dArray:
            create_parcel_file(qname, d['name'], d['fields'], d['keyFields'], d['childrenInterAttr'], d['conversionFunctions'], d['usecols'],
                               jsonpath,
                               outputpath)


def parcel_include_list(tbls: List[str], has_projection: Dict[str, bool]) -> str:
    return '\n'.join([f'#include "{tbl}Parcel.h"' for tbl in tbls] + [f'#include "PROJECTED_{tbl}Parcel.h"' for tbl in tbls if has_projection[tbl]])


def table_list(tbls: List[str]) -> str:
    return ', '.join([tname + 'Table' for tname in tbls])


def table_ref_list(tbls: List[str]) -> str:
    ref_list = ''
    i = 1
    for tname in tbls:
        if i > 1:
            ref_list += ', '
        ref_list += tname + 'Table& ' + tname.lower() + '_tbl'
        i += 1

    return ref_list


def split_table_list(tbls: List[str], has_projection: Dict[str, bool]) -> str:
    return ', '.join([f'{("" if not has_projection[tname] else "PROJECTED_") + tname}SplitTable' for tname in tbls])


def split_table_ref_list(tbls: List[str], has_projection: Dict[str, bool]) -> str:
    ref_list = ''
    i = 1
    for tname in tbls:
        if i > 1:
            ref_list += ', '
        ref_list += ("" if not has_projection[tname] else "PROJECTED_") + tname + 'SplitTable& split_' + tname.lower() + 'tbl'
        i += 1

    return ref_list


def bottom_up_body(tblPostOrder: List[str], tree: Dict[str, Dict[str, Union[str, List[str]]]]) -> str:
    calls = ''

    i = 0
    for tblname in tblPostOrder:
        if tree[tblname]['parent'] is None:
            return calls  # reached root, which must be last

        if i > 0:
            calls += '\n\t\t'

        calls += f'oneBottomUp<{tree[tblname]["parent"] + "Parcel"}, {tblname + "Parcel"},' \
            f' {tblname + "Key"}>({tree[tblname]["parent"].lower() + "_tbl"}, {tblname.lower() + "_tbl"});'

        i += 1

    return calls


def top_down_body(tblPreOrder: List[str], tree: Dict[str, Dict[str, Union[str, List[str]]]]) -> str:
    calls = ''

    i = 0
    for tblname in tblPreOrder:
        if tree[tblname]['children'] is []:
            continue

        for childTblName in tree[tblname]['children']:
            if i > 0:
                calls += '\n\t\t'

            calls += f'oneTopDown<{childTblName + "Parcel"}, {tblname + "Parcel"}, {childTblName + "Key"}>' \
                f'({childTblName.lower() + "_tbl"}, {tblname.lower() + "_tbl"});'

            i += 1

    return calls


def create_single_weighter(qname: str, tblname: str, children: List[str], has_projection: Dict[str, bool]) -> str:
    pref = 'PROJECTED_' if has_projection[tblname] else ''
    cprefs = [('PROJECTED_' if has_projection[tbl] else '') for tbl in children]
    comment = "//leaf\n" if not children else "//internal node\n"
    newline = "\n\t" if children else ""

    weighter = f"#ifdef PROJECTION_{qname}\n"

    weighter += f'struct {tblname}Weighter : AbstractSingleTableWeighter<{pref + tblname}Key, {pref + tblname}Parcel'
    weighter += ''.join(f', {(cprefs[children.index(childname)]) + childname}SplitTable' for childname in children)
    weighter += f'>' + ' {'
    weighter += comment
    weighter += f'\tinline void weightTable({pref + tblname}SplitTable& split_{tblname.lower()}tbl'
    weighter += ''.join(
        [f', const {(cprefs[children.index(childname)]) + childname}SplitTable& split_{childname.lower()}tbl' for childname in children])
    weighter += ') override {'
    weighter += ''.join([f'\n\t\tweightingStep(split_{tblname.lower()}tbl, split_{childname.lower()}tbl);' for childname in children])
    weighter += f'{newline}' + '}'
    weighter += "\n};\n"

    weighter += "#else\n"
    weighter += f'struct {tblname}Weighter : AbstractSingleTableWeighter<{tblname}Key, {tblname}Parcel'
    weighter += ''.join(f', {childname}SplitTable' for childname in children)
    weighter += f'>' + ' {'
    weighter += comment
    weighter += f'\tinline void weightTable({tblname}SplitTable& split_{tblname.lower()}tbl'
    weighter += ''.join(
        [f', const {childname}SplitTable& split_{childname.lower()}tbl' for childname in children])
    weighter += ') override {'
    weighter += ''.join([f'\n\t\tweightingStep(split_{tblname.lower()}tbl, split_{childname.lower()}tbl);' for childname in children])
    weighter += f'{newline}' + '}'
    weighter += "\n};\n"
    weighter += "#endif\n"

    return weighter


def single_weighters(qname: str, postorder: List[str], tree: Dict[str, Dict[str, Union[str, List[str]]]], has_projection: Dict[str, bool]):
    return '\n\n'.join([create_single_weighter(qname, tbl, tree[tbl]['children'], has_projection) for tbl in postorder])


def query_weighter_body(postorder: List[str], tree: Dict[str, Dict[str, Union[str, List[str]]]]) -> str:
    params = {}

    for tbl in postorder:
        params[tbl] = ''.join([f', split_{child.lower()}tbl' for child in tree[tbl]['children']])

    return '\n\n\t\t'.join([f'{tbl}Weighter().weight(split_{tbl.lower()}tbl{params[tbl]});' for tbl in postorder])


def preprocessing_tables_vars(tbls: List[str]) -> str:
    return '\t\t'.join([f"{tbl}Table {tbl.lower()}tbl;\n" for tbl in tbls])


def preprocessing_translator_vars(tbls: List[str]) -> str:
    return '\n\t'.join([f"{tbl}Translator {tbl.lower()}translator;" for tbl in tbls])


def preprocessing_load_from_file(tbls: List[str]) -> str:
    return '\n\t\t'.join([f'{tbl.lower()}tbl.loadFromFile(filenames.at("{tbl}"), numLines.at("{tbl}"));' for tbl in tbls])


def preprocessing_split_tables_vars(tbls: List[str]) -> str:
    return '\t\t'.join([f"{tbl}SplitTable split_{tbl.lower()}tbl;\n" for tbl in tbls])


def preprocessing_split_tables_fields(tbls: List[str]) -> str:
    return '\t'.join([f"{tbl}SplitTable split_{tbl.lower()}tbl;\n" for tbl in tbls])


def preprocessing_split_tables_fields_with_projection(tbls: List[str], projection: Dict[str, bool]) -> str:
    lines = []
    for tbl in tbls:
        if projection[tbl]:
            lines += [f"PROJECTED_{tbl}SplitTable split_{tbl.lower()}tbl;"]
        else:
            lines += [f"{tbl}SplitTable split_{tbl.lower()}tbl;"]

    return '\n\t'.join(lines)


def preprocessing_split_tables_from_tables(tbls: List[str]) -> str:
    return '\n\t\t'.join([f"split_{tbl.lower()}tbl.loadFromTable({tbl.lower()}tbl);" for tbl in tbls])


def preprocessing_tables_var_list(tbls: List[str]) -> str:
    return ', '.join([f'{tbl.lower()}tbl' for tbl in tbls])


def preprocessing_split_tables_var_list(tbls: List[str]) -> str:
    return ', '.join([f'split_{tbl.lower()}tbl' for tbl in tbls])


def create_find_function(name: str, tblname: str, children: List[str], has_projection: Dict[str, bool]) -> str:
    function_template: str = open('FindAnswerFunctionTemplate').read()
    function_template = substitute(function_template, 'query_name', name)
    function_template = substitute(function_template, 'tblname', tblname)
    function_template = substitute(function_template, 'tblname_lower', tblname.lower())
    function_template = substitute(function_template, 'child_indx_refs', ''.join([', ll& j_' + child.lower() for child in children]))
    function_template = substitute(function_template, 'child_indx_ref_assignment',
                                   '\n\t\t'.join([f'j_{children[i].lower()} = new_indices[' + str(i) + '];' for i in range(0, len(children))]))
    function_template = substitute(function_template, 'is_projected', "PROJECTED_" if has_projection[tblname] else "")

    if not children:
        function_template = substitute(function_template, 'new_indices', '//')
    else:
        function_template = substitute(function_template, 'new_indices', '')

    function_template = substitute(function_template, 'caps', '{' + (',\n' + '\t' * 18).join(
        [f'split_{child.lower()}tbl.buckets[answer.to<{child}Key>()].totalWeight' for child in children]) + '}')
    function_template = substitute(function_template, 'caps_2', '{' + (',\n' + '\t' * 18).join(
        [f'split_{child.lower()}tbl.buckets[answer.to<{"PROJECTED_" if has_projection[child] else ""}{child}Key>()].totalWeight' for child in
         children]) + '}')

    return function_template


def create_index_function(name: str, tblname: str, children: List[str], has_projection: Dict[str, bool]) -> str:
    function_template: str = open('FindIndexFunctionTemplate').read()
    function_template = substitute(function_template, 'query_name', name)
    function_template = substitute(function_template, 'tblname', tblname)
    function_template = substitute(function_template, 'tblname_lower', tblname.lower())
    function_template = substitute(function_template, 'child_indx', ''.join([', ll j_' + child.lower() for child in children]))
    function_template = substitute(function_template, 'child_indx_call', '{' + ', '.join(['j_' + child.lower() for child in children]) + '}')
    function_template = substitute(function_template, 'is_projected', "PROJECTED_" if has_projection[tblname] else "")

    if not children:
        function_template = substitute(function_template, 'combine_comment_start', '/*')
        function_template = substitute(function_template, 'combine_comment_end', '*/')
    else:
        function_template = substitute(function_template, 'combine_comment_start', '')
        function_template = substitute(function_template, 'combine_comment_end', '')

    function_template = substitute(function_template, 'caps', '{' + (',\n' + '\t' * 18).join(
        [f'split_{child.lower()}tbl.buckets[answer.to<{child}Key>()].totalWeight' for child in children]) + '}')
    function_template = substitute(function_template, 'caps_2', '{' + (',\n' + '\t' * 18).join(
        [f'split_{child.lower()}tbl.buckets[answer.to<{"PROJECTED_" if has_projection[child] else ""}{child}Key>()].totalWeight' for child in
         children]) + '}')

    return "\n".join([line for line in function_template.splitlines()])


def finder_functions(name: str, tbls: List[str], tree, has_projection: Dict[str, bool]):
    return '\n\n\t'.join(create_find_function(name, tbl, tree[tbl]['children'], has_projection) for tbl in tbls)


def indexer_functions(name: str, tbls: List[str], tree, has_projection: Dict[str, bool]):
    return '\n\n\t'.join(create_index_function(name, tbl, tree[tbl]['children'], has_projection) for tbl in tbls)


def replace_js(root: str, tbls: List[str], method="find_answer") -> str:
    if method == "find_answer":
        return ', '.join(['j_' + tbl.lower() for tbl in tbls if tbl != root])

    elif method == "find_index":
        return ', '.join(['j_' + tbl.lower() for tbl in tbls])


def access_calls(root: str, tree: Dict[str, Dict[str, Union[str, List[str]]]], preorder: List[str]) -> str:
    calls = [
        f'find_answer_{tbl}(ans, {"j" if root == tbl else f"j_{tbl.lower()}"}{"".join([f", j_{child.lower()}" for child in tree[tbl]["children"]])});'
        for tbl in preorder]
    return '\n\t\t'.join(calls)


def index_calls(tree: Dict[str, Dict[str, Union[str, List[str]]]], postorder: List[str]) -> str:
    temp_template = "if(!{{call}}) {\n\t\t\treturn -1;\n\t\t}\n"
    calls = [substitute(temp_template, "call",
                        f'find_index_{tbl}(ans, {", ".join([f"j_{child.lower()}" for child in tree[tbl]["children"]])}{", " if len(tree[tbl]["children"]) > 0 else ""}{f"j_{tbl.lower()}"})')
             for tbl in postorder]
    return '\n\t\t'.join(calls)


def projection_and_split(tbls: List[str], projection: Dict[str, bool]) -> str:
    lines = []

    for tbl in tbls:
        if not projection[tbl]:
            lines += [f"split_{tbl.lower()}tbl.loadFromTable({tbl.lower()}tbl);"]
        else:
            tempvar = f'{tbl.lower()}tbl.project<{"PROJECTED_" + tbl + "Parcel"}>()'
            lines += [f'split_{tbl.lower()}tbl.loadFromTable({tempvar});']

    return '\n\t\t'.join(lines)


def create_index_file(qname: str, name: str, root: str, tbls: List[str], projection: Dict[str, bool], postorder: List[str], preorder: List[str],
                      tree: Dict[str, Dict[str, Union[str, List[str]]]], outputpath: str) -> None:
    # postorder =  child before parent
    # preorder = reverse of post-order, parent before child

    outputFilename: str = name + "Index.h"
    code = open('IndexTemplate').read()

    code = substitute(code, 'query_name', name)
    code = substitute(code, 'root', root.lower())
    code = substitute(code, 'include_parcels', parcel_include_list(tbls, projection))
    code = substitute(code, 'table_list', table_list(tbls))
    code = substitute(code, 'table_ref_list', table_ref_list(tbls))
    code = substitute(code, 'split_table_list', split_table_list(tbls, {t: False for t in tbls}))
    code = substitute(code, 'maybe_projected_split_table_list', split_table_list(tbls, projection))
    code = substitute(code, 'split_table_ref_list', split_table_ref_list(tbls, {t: False for t in tbls}))
    code = substitute(code, 'maybe_projected_split_table_ref_list', split_table_ref_list(tbls, projection))
    code = substitute(code, 'bottom_up_body', bottom_up_body(postorder, tree))
    code = substitute(code, 'top_down_body', top_down_body(preorder, tree))
    code = substitute(code, 'single_weighters', single_weighters(name, postorder, tree, projection))
    code = substitute(code, 'weight_body', query_weighter_body(postorder, tree))
    code = substitute(code, 'tables_local_vars_decl', preprocessing_tables_vars(tbls))
    code = substitute(code, 'translators_fields', preprocessing_translator_vars(tbls))
    code = substitute(code, 'load_tables_from_files', preprocessing_load_from_file(tbls))
    code = substitute(code, 'split_tables_fields', preprocessing_split_tables_fields(tbls))
    code = substitute(code, 'split_tables_fields_with_projection', preprocessing_split_tables_fields_with_projection(tbls, projection))
    code = substitute(code, 'split_tables_from_tables', preprocessing_split_tables_from_tables(tbls))
    code = substitute(code, 'tables_local_vars_list', preprocessing_tables_var_list(tbls))
    code = substitute(code, 'split_table_var_list', preprocessing_split_tables_var_list(tbls))
    code = substitute(code, 'child_find_answer_functions', finder_functions(name, tbls, tree, projection))
    code = substitute(code, 'js', replace_js(root, tbls))
    code = substitute(code, 'js_index', replace_js(root, tbls, "find_index"))
    code = substitute(code, 'num_tbls', str(len(tbls)))
    code = substitute(code, 'access_calls', access_calls(root, tree, preorder))
    code = substitute(code, 'child_find_index_functions', indexer_functions(name, tbls, tree, projection))
    code = substitute(code, 'index_calls', index_calls(tree, postorder))
    code = substitute(code, 'projection_and_split', projection_and_split(tbls, projection))

    for t in tbls:
        code = code.replace(f"{t}Parcel", f"{qname}_{t}Parcel")
        code = code.replace(f"{t}Key", f"{qname}_{t}Key")
        code = code.replace(f"{t}Table", f"{qname}_{t}Table")
        code = code.replace(f"{t}SplitTable", f"{qname}_{t}SplitTable")
        code = code.replace(f"{t}Weighter", f"{qname}_{t}Weighter")

    code = code.replace('\t', 4 * ' ')
    open(outputpath + outputFilename, 'w+').write(code)


def generate_index_file_from_json(qname: str, jsonpath: str, outputpath: str) -> None:
    with open(jsonpath + 'IndexParams.json') as f:
        d = json.load(f)

    create_index_file(qname, d['name'], d['root'], d['tbls'], d['projection'], d['postorder'], d['preorder'], d['tree'], outputpath)


def answer_fields(allFields: List[str], allTypes: Dict[str, str]) -> str:
    return '\n\t'.join([f'{allTypes[fieldName]} {fieldName};' for fieldName in allFields])


def print_answer(allFields: List[str], allTypes: Dict[str, str]) -> str:
    fieldsAndTypes = [(allTypes[field], field) for field in allFields]
    return print_body(fieldsAndTypes)


def to_string_body(fieldList: List[str]) -> str:
    if fieldList is []:
        return 'return "{}"'

    body = 'stringstream st;\n\t\tst << "{"' + f' << {fieldList[0]};\n'
    body += '\n'.join([f'\t\tst << ", " << {f};' for f in fieldList[1:]])
    body += '\n\t\tst << "}";\n\t\treturn st.str();'

    return body


def answer_hash(allFields: List[str], allTypes: Dict[str, str]) -> str:
    fieldsAndTypes = [(allTypes[field], field) for field in allFields]
    return hash_body(fieldsAndTypes)


def answer_equal_to(allFields: List[str], allTypes: Dict[str, str]) -> str:
    fieldsAndTypes = [(allTypes[field], field) for field in allFields]
    return equal_to_condition(fieldsAndTypes)


def answer_to_parcel(name: str, tblname: str, fields: List[str], label: str, prefix: str) -> str:
    return f'template<> {prefix}{tblname}{label} {name}Answer::to<{prefix}{tblname}{label}>() const' + ' {\n' + '\treturn {' + ', '.join(
        fields) + '};\n' + '}'


def to_spec(name: str, fieldsDict: Dict[str, List[str]], label: str, has_projection: Dict[str, bool]) -> str:
    allTables = list(fieldsDict.keys())
    return '\n\n'.join([answer_to_parcel(name, t, fieldsDict[t], label, "PROJECTED_" if has_projection[t] else "") for t in allTables])


def answer_from_parcel(name: str, tblname: str, fields: List[str], prefix: str):
    return f'template<> void {name}Answer::set<{prefix + tblname}Parcel>(const {prefix + tblname}Parcel& p) ' + '{\n\t' + '\n\t'.join(
        [f'{field} = p.{field};' for field in fields]) + '\n}'


def set_spec(name: str, fieldsDict: Dict[str, List[str]], has_projection: Dict[str, bool]) -> str:
    return '\n\n'.join([answer_from_parcel(name, t, fieldsDict[t], "PROJECTED_" if has_projection[t] else "") for t in list(fieldsDict.keys())])


def include_parcels(allTables: List[str]) -> str:
    return '\n'.join([f'#include "{tbl}Parcel.h"' for tbl in allTables])


def include_maybe_projected_parcels(varsDict: Dict[str, List[str]], freevarsDict: Dict[str, List[str]]) -> str:
    lines = []
    for T in varsDict.keys():
        lines += [f'#include "{"" if varsDict[T] == freevarsDict[T] else "PROJECTED_"}{T}Parcel.h"']
    return '\n'.join(lines)


def create_answer_file(qname: str, jsonpath: str, outputpath: str):
    # QueryFields refers to the query after it has been reduced to an acyclic query with no projection
    with open(jsonpath + 'QueryFields.json') as f:
        d = json.load(f)

        name: str = d['name']
        allvars: List[str] = d['vars']
        freevars: List[str] = d['freevars']
        types: Dict[str, str] = d['types']
        varsDict: Dict[str, List[str]] = d['varsDict']
        freevarsDict: Dict[str, List[str]] = d['freevarsDict']
        keyvarsDict: Dict[str, List[str]] = d['keyvarsDict']
        freekeyvarsDict: Dict[str, List[str]] = d['freekeyvarsDict']
        tbls: List[str] = list(varsDict.keys())
        has_projection: Dict[str, bool] = {k: (varsDict[k] != freevarsDict[k]) for k in varsDict}
        no_projection: Dict[str, bool] = {k: False for k in varsDict}

        code = open('AnswerTemplate').read()

        code = substitute(code, 'query_name', name)
        code = substitute(code, 'vars', answer_fields(allvars, types))
        code = substitute(code, 'freevars', answer_fields(freevars, types))
        code = substitute(code, 'print_body', print_answer(allvars, types))
        code = substitute(code, 'print_body_2', print_answer(freevars, types))
        code = substitute(code, 'to_string_body', to_string_body(allvars))
        code = substitute(code, 'to_string_body_2', to_string_body(freevars))
        code = substitute(code, 'hash_combine', answer_hash(allvars, types))
        code = substitute(code, 'hash_combine_2', answer_hash(freevars, types))
        code = substitute(code, 'equal_to_conditions', answer_equal_to(allvars, types))
        code = substitute(code, 'equal_to_conditions_2', answer_equal_to(freevars, types))
        code = substitute(code, 'to_specializations',
                          to_spec(name, keyvarsDict, "Key", no_projection) + "\n\n" + to_spec(name, varsDict, "Parcel", no_projection))
        code = substitute(code, 'to_specializations_2',
                          to_spec(name, freekeyvarsDict, "Key", has_projection) + "\n\n" + to_spec(name, freevarsDict, "Parcel", has_projection))
        code = substitute(code, 'set_specializations', set_spec(name, varsDict, no_projection))
        code = substitute(code, 'set_specializations_2', set_spec(name, freevarsDict, has_projection))
        code = substitute(code, 'include_all_parcels', include_parcels(tbls))
        code = substitute(code, 'include_all_parcels_2', include_maybe_projected_parcels(varsDict, freevarsDict))

        for t in tbls:
            code = code.replace(f"{t}Parcel", f"{qname}_{t}Parcel")
            code = code.replace(f"{t}Key", f"{qname}_{t}Key")
            code = code.replace(f"{t}Table", f"{qname}_{t}Table")
            code = code.replace(f"{t}SplitTable", f"{qname}_{t}SplitTable")
            code = code.replace(f"{t}Weighter", f"{qname}_{t}Weighter")

        code = code.replace('\t', 4 * ' ')
        open(outputpath + name + 'Answer.h', 'w+').write(code)


def generate_enumeration_test(name: str, outputpath: str):
    with open('RandomEnumerationTestTemplate') as f:
        code = substitute(f.read(), 'query_name', name).replace('\t', 4 * ' ')
        open(outputpath + name + '_enumeration_test.cpp', 'w+').write(code)


def generate_timing_test(name: str, outputpath: str):
    with open('TimingTestTemplate') as f:
        code = substitute(f.read(), 'query_name', name).replace('\t', 4 * ' ')
        open(outputpath + name + '_timing_test.cpp', 'w+').write(code)


def generate_index_of_test(name: str, outputpath: str):
    with open('IndexOfTestTemplate') as f:
        code = f.read()

        code = substitute(code, 'query_name', name)

        code = code.replace('\t', 4 * ' ')
        open(outputpath + name + '_index_of_test.cpp', 'w+').write(code)


def from_parcel(fields):
    fields_names = [f[1] for f in fields]
    return 'return {' + ', '.join([f'p.{f}' for f in fields_names]) + '};'


def maybe_projected_child_includes(child_tbls: List[str], projected_tbls: List[str]) -> str:
    return '\n'.join([f'#include "{"PROJECTED_" if t in projected_tbls else ""}{t}Parcel.h"' for t in child_tbls])


def maybe_projected_children_conversion(name: str, childrenInterAttr: Dict[str, List[str]], tbls_with_projection: List[str]) -> str:
    lines = []

    for childName in childrenInterAttr.keys():
        lines += [
            f'template<> {"PROJECTED_" if childName in tbls_with_projection else ""}{childName}Key PROJECTED_{name}Parcel::to<{"PROJECTED_" if childName in tbls_with_projection else ""}'
            f'{childName}Key>() const' + ' {', '\treturn {' + ', '.join(childrenInterAttr[childName]) + '};\n', '}\n']

    return '\n'.join(lines)


def create_projected_parcel_file(qname: str, name: str, fields: List[Tuple[str, str]], keyFields: List[str],
                                 childrenInterAttr: Dict[str, List[str]], tbls_with_projection: List[str], outputpath: str) -> None:
    # ProjectedParcelCreateList should be updated to the tables AFTER PROJECTION (in terms of the attributes & their intersections

    code = open('ProjectedParcelTemplate').read()

    code = substitute(code, 'name', name)
    code = substitute(code, 'query_name', qname)
    code = substitute(code, 'fields', field_decl_list(fields))
    code = substitute(code, 'print_body', print_body(fields))
    code = substitute(code, 'key_fields_init_list', to_key_body(keyFields))
    code = substitute(code, 'equal_to_conditions', equal_to_condition(fields))
    code = substitute(code, 'hash_combine', hash_body(fields))
    code = substitute(code, 'maybe_projected_child_conversion', maybe_projected_children_conversion(name, childrenInterAttr, tbls_with_projection))
    code = substitute(code, 'from_body', from_parcel(fields))
    code = substitute(code, 'key_fields', key_fields_decl_list(fields, keyFields))
    code = substitute(code, 'key_print_body', key_fields_print(keyFields))
    code = substitute(code, 'key_hash_combine', key_hash_body(keyFields))
    code = substitute(code, 'key_equal_to_conditions', key_equal_to_condition(keyFields))
    code = substitute(code, 'maybe_projected_child_includes', maybe_projected_child_includes(list(childrenInterAttr.keys()), tbls_with_projection))
    code = substitute(code, 'full_parcel_include', f'#include "{name}Parcel.h"')

    code = code.replace(f"{name}Parcel", f"{qname}_{name}Parcel")
    code = code.replace(f"{name}Key", f"{qname}_{name}Key")
    code = code.replace(f"{name}PARCEL", f"{qname}_{name}PARCEL")
    code = code.replace(f"{name}Table", f"{qname}_{name}Table")
    code = code.replace(f"{name}SplitTable", f"{qname}_{name}SplitTable")

    for c in list(childrenInterAttr.keys()):
        code = code.replace(f"{c}Parcel", f"{qname}_{c}Parcel")
        code = code.replace(f"{c}Key", f"{qname}_{c}Key")

    code = code.replace('\t', 4 * ' ')
    # name = "C"
    outputFilename: str = f"PROJECTED_{qname}_{name}Parcel.h"
    open(outputpath + outputFilename, 'w+').write(code)


def generate_projected_parcels_from_json(qname: str, jsonpath: str, outputpath: str) -> None:
    with open(jsonpath + 'ProjectedParcelCreateList.json') as f:
        d = json.load(f)
        dArray = d['array']
        dTBLS = d['tbls']

        for d in dArray:
            create_projected_parcel_file(qname, d['name'], d['fields'], d['keyFields'], d['childrenInterAttr'], dTBLS, outputpath)


def generate_makefile(name: str, outputpath: str):
    with open('MakefileTemplate') as f:
        code = substitute(f.read(), 'name', name)
        open(outputpath + 'Makefile', 'w+').write(code)


if __name__ == '__main__':

    queryname = None
    jsonpath = None
    outputpath = None

    if len(sys.argv) == 2:
        queryname = str(sys.argv[1])
        jsonpath = queryname + "/"
        outputpath = queryname + "/files/"
    elif len(sys.argv) == 7 and sys.argv[1] == '--query-name' and sys.argv[3] == '--query-path' and sys.argv[5] == '--output-path':
        queryname = str(sys.argv[2])
        jsonpath = str(sys.argv[4])
        outputpath = str(sys.argv[6])
    else:
        print("usage: gen.py --query-name <name> --query-path <path_to_json_files> --output-path <path_to_output_files> or gen.py <name>")
        exit(0)

    generate_parcels_from_json(queryname, jsonpath, outputpath)
    generate_projected_parcels_from_json(queryname, jsonpath, outputpath)
    generate_index_file_from_json(queryname, jsonpath, outputpath)
    create_answer_file(queryname, jsonpath, outputpath)
    generate_enumeration_test(queryname, outputpath)
    # generate_index_of_test(queryname, outputpath)
    generate_timing_test(queryname, outputpath)
    generate_makefile(queryname, outputpath)
