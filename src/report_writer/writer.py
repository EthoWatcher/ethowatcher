from xlsxwriter import Workbook
import argparse

def read_ls_comand(path:str):
    def map_s(st_o:str):
        return st_o.replace("\n","")

    def map_str_tuple(st_o:str):
        ls_para = st_o.split(";")

        if ls_para[2] == '0':
            return (ls_para[0], ls_para[1], False)
        else:
            return (ls_para[0], ls_para[1], True)


    with open(path) as f:
        lines = f.readlines()

    ls_lines_n = list(map(map_s, lines))
    ls_lines_remove = list(filter(lambda x: len(x.split(";")) >=3, ls_lines_n ))


    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\gooo_1.txt', 'w') as f:
    #     f.write(path)
    #     for pos in ls_lines_remove:
    #         f.write("\n")
    #         f.write(str(pos))   
    
    ls_data = list(map(map_str_tuple, ls_lines_remove))

    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\gooo_2.txt', 'w') as f:
    #     f.write(path)
    #     for pos, text, r_number in ls_data:
    #         f.write("\n")
    #         f.write(str(pos)) 



    ls_line = list(filter(lambda x: len(x) == 3, ls_data))
    return ls_line

def create_excel_file(ls_comands, path):
    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\gooo_25.txt', 'w') as f:
    #     f.write(path)

    wk = Workbook(path)

    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\gooo_3.txt', 'w') as f:
    #     f.write(path)
    #     for pos, text, r_number in ls_comands:
    #         f.write("\n")
    #         f.write(str(pos))
    
    worksheet = wk.add_worksheet()
    for pos, text, r_number in ls_comands:
        if r_number:
            worksheet.write(pos, float(text))
        else:
            worksheet.write(pos, text)
    
    wk.close()



def main():
    parser = argparse.ArgumentParser(description="teste" )
    parser.add_argument("path", help="some_Text")
    args = parser.parse_args()
    path:str = args.path
    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\readme_chegou.txt', 'w') as f:
    #     f.write("aaaaaaaaaaaaaaaaaaaaaaa")

    
    # path = "C:\\doutorado\\software\\Terminando o Ethowatcher\\experimento\\de23_tkin0Total Area_xlsx.xlsx"
    # path = "C:\\doutorado\software\\Terminando o Ethowatcher\\experimento\\123adszxc_tkin0Total Area_xlsx.xlsx"
    path_replace = path.replace("\"","")
    # with open('C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\readme.txt', 'w') as f:
    #     f.write(path)
    #     f.write("\n")
    #     f.write(path_replace)


    ls_comands = read_ls_comand(path_replace)
    create_excel_file(ls_comands, path_replace + "_saida.xlsx")
    print(f"write_fix:{path_replace}" )

if __name__ == "__main__":
    main()

    # conda activate etho39
   