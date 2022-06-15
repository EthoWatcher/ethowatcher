
# https://github.com/jmcnamara/XlsxWriter
import argparse
import json
import escreve_xlsx as es

# python gera_relatorio.py  ./demo2.xlsx {\"name\":\"joao\"} 
# python gera_relatorio.py ./sss.xlsx "{\"teste\":[0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 2 , 2 , 2]}"
"""
    python gera_relatorio.py ./sss1.xlsx "{'teste':[0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 2 , 2 , 2], 's': [12]}"
    python gera_relatorio.py ./sss1.xlsx "{'teste':[0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 2 , 2 , 2]}"
    python gera_relatorio.py C:/saida_teste/muitos.xlsx
    python gera_relatorio.py C:/saida_teste/figura_tese.xlsx
    python gera_relatorio.py "C:/saida_teste/dados_reais_2kamostras_novo_algo_categorias_dev.xlsx"
    python gera_relatorio.py "C:/saida_teste/saida_novo_rand2_seed.xlsx" 
"""
# 


parser = argparse.ArgumentParser(description="teste" )

parser.add_argument("path", help="some_Text")
# parser.add_argument("t", help="some_Text")
args = parser.parse_args()




if __name__ == '__main__':
    # print(cilinder(args.r,args.h))
    # text = args.t
    path = args.path
    with open(path + ".txt", 'r') as file:
        text = file.read()

    
    # print(text)
    text = text.replace("\'", "\"")
    text = text.replace("nan", "\"nan\"")
    data = json.loads(text)

    es.create_excel_file(data, path)


    # print(s)
