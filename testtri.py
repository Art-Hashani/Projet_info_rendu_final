import clang.cindex

def print_code(cursor, source_file_path="test.c"):
    extent = cursor.extent
    with open(source_file_path, 'r') as source_file:
        lines = source_file.readlines()[extent.start.line - 1:extent.end.line]
        code_snippet = ''.join(lines)
        print(code_snippet)

def check_for_exchange(cursor, condition=False):
    if cursor.kind == clang.cindex.CursorKind.FOR_STMT:
        # print(cursor.kind)
        cursor_interieur_boucle = list(cursor.get_children())[3]
        return check_for_exchange(cursor_interieur_boucle, condition)
    elif condition is True:
        if cursor.kind == clang.cindex.CursorKind.COMPOUND_STMT:
            nb_binary_op_array = 0
            for child in cursor.get_children():
                # print_code(child)
                # print(f"\t\t{child.kind}")
                code_affectation = list(child.get_children())
                gauche = code_affectation[0]
                # print(f"\t\t\t{gauche.kind}")
                droite = code_affectation[1]
                # print(f"\t\t\t{droite.kind}")
                if gauche.kind == clang.cindex.CursorKind.ARRAY_SUBSCRIPT_EXPR:
                    nb_binary_op_array += 1
            if nb_binary_op_array == 2:
                return True
            else:
                return False

    elif cursor.kind == clang.cindex.CursorKind.IF_STMT:
        # print(f"\t{cursor.kind}")
        cursor_interieur_if = list(cursor.get_children())[1]
        return check_for_exchange(cursor_interieur_if, condition=True)

    else:
        for child in cursor.get_children():
            return check_for_exchange(child, condition)

    return False

def param(cursor):
    for child in cursor.get_children():
        # print("Child Kind:", child.type.kind)

        if child.kind == clang.cindex.CursorKind.PARM_DECL:
            if child.type.kind == clang.cindex.TypeKind.POINTER:
                return True
            if child.type.kind == clang.cindex.TypeKind.INCOMPLETEARRAY:
                return True
            if child.type.kind == clang.cindex.TypeKind.CONSTANTARRAY:
                return True
    return False


def imbrique(cursor,has_outer_loop=False):
    for child in cursor.get_children():
        # Vérifiez si le curseur représente un paramètre de fonction
        if child.kind == clang.cindex.CursorKind.PARM_DECL:
            param_type = child.type
        # Vérifiez si la fonction contient une boucle
        if child.kind == clang.cindex.CursorKind.FOR_STMT or child.kind == clang.cindex.CursorKind.WHILE_STMT:
            # Vérifiez si la fonction a déjà une boucle extérieure
            #print(child.kind)
            if has_outer_loop is True:
                return True
            return imbrique(child,True)
        if child.kind == clang.cindex.CursorKind.COMPOUND_STMT:
           # print(has_outer_loop)
            return imbrique(child,has_outer_loop)

def cursimbrique(cursor,has_outer_loop=False):
    for child in cursor.get_children():
        # Vérifiez si le curseur représente un paramètre de fonction
        if child.kind == clang.cindex.CursorKind.PARM_DECL:
            param_type = child.type
        # Vérifiez si la fonction contient une boucle
        if child.kind == clang.cindex.CursorKind.FOR_STMT or child.kind == clang.cindex.CursorKind.WHILE_STMT:
            # Vérifiez si la fonction a déjà une boucle extérieure
            #print(child.kind)
            if has_outer_loop is True:
                return cursor
            return cursimbrique(child,True)
        if child.kind == clang.cindex.CursorKind.COMPOUND_STMT:
           # print(has_outer_loop)
            return cursimbrique(child,has_outer_loop)


def is_import(cursor):
    return cursor.location.file.name != "test.c"


def main():
    # Remplacez le chemin du fichier par le chemin de votre fichier C
    file_path = "test.c"

    # Configurez l'index Clang
    index = clang.cindex.Index.create()
    translation_unit = index.parse(file_path)

    if not translation_unit:
        print("Erreur lors de l'analyse du fichier.")
        return
    # Parcourez toutes les déclarations de fonction dans le fichier
    for cursor in translation_unit.cursor.get_children():
        if cursor.kind == clang.cindex.CursorKind.FUNCTION_DECL and not is_import(cursor):
            print(f"\nFunction: {cursor.spelling}")
            print(cursor.location.file.name)

            # Vérifiez si la fonction a des boucles imbriquées
            if imbrique(cursor) is True:
                cursor_imbr = cursimbrique(cursor)
                if check_for_exchange(cursor_imbr):
                    print("C'est un algorithme de tri.")
            else:
                print("Ce n'est pas un algorithme de tri.")

if __name__ == "__main__":
    main()
