import json
import escreve_xlsx as es

# path = "C:\\saida_teste\\figura_tese_dev.xlsx"
path = "C:\\saida_teste\\new_report_editing_table.xlsx"
with open(path + ".txt", 'r') as file:
    text = file.read()


# print(text)
text = text.replace("\'", "\"")
text = text.replace("nan", "\"nan\"")
data = json.loads(text)

es.create_excel_file(data, path)