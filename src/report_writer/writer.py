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

    ls_line = list(map(map_str_tuple, map(map_s, lines)))
    return ls_line

def create_excel_file(ls_comands, path):
    wk = Workbook(path)
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
    # parser.add_argument("t", help="some_Text")
    args = parser.parse_args()
    path = args.path
    # path = "C:\\doutorado\software\\Terminando o Ethowatcher\\experimento\\123adszxc_tkin0Total Area_xlsx.xlsx"
    ls_comands = read_ls_comand(path)
    create_excel_file(ls_comands, path+"_saida.xlsx")

if __name__ == "__main__":
    main()
   