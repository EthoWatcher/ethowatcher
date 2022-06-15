import numpy as np
import extrai_descritor as ed

lst_dados = [43, 54, 56, 61, 62, 66, 68, 69, 69, 70, 71, 72, 77, 78, 79, 85, 87, 88, 89, 93, 95, 96, 98, 99, 99]

confidence = 0.95
ls_conf = [100*(1-confidence)/2,100*(1-(1-confidence)/2)]
print(np.percentile(lst_dados,ls_conf ))
# print(ed.percentil_custom(lst_dados, ls_conf))



