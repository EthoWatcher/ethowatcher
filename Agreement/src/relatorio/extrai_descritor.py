from typing import List
import numpy as np
import math


def get_descritores_max(r_max, data):
    def map_categ(data, descritor, r_max):
        def map_des(linha):
            if r_max:
                return linha['catalogo_var_max'][descritor]
            else:
                return linha['catalogo_var'][descritor]

        return list(map(map_des, data['varios_kappa'] ))
    
    ls_descritores = list(data['varios_kappa'][0]['catalogo_var'].keys())
    ls = {}

    for descritor in ls_descritores:
        r_calcula = descritor != "matriz_concordancia"
        if r_calcula:
            ls[descritor] = map_categ(data, descritor, r_max)
    
    return ls


# TODO: find a way to calculate percentil
# def percentil_custom(ls_dados: List, ls_percentil):
#     l_d = ls_dados.copy()
#     tamanho = len(l_d)
#     l_d.sort()
#     def calc_percentil(per):
#         index = per * tamanho

#         r_index_int = index.is_integer()
#         if r_index_int:
#             return (l_d[int(index)] + l_d[int(index)])/2
#         else:
#             # alpha = 1
#             # beta = 1
#             # frac, whole = math.modf(index)
#             # i = (per*100 - alpha)/(tamanho - alpha - beta +1)
#             # frac, whole = math.modf(i)

#             return i


#     inferior = calc_percentil(ls_percentil[0]/100)
#     superior = calc_percentil(ls_percentil[1]/100)
#     return (inferior, superior)



def confidence_percentil(lst_dados, confidence=0.95):
    # lst_dados = list(filter(lambda x: x!="nan", lst_dados))
    con_max = np.percentile(lst_dados,[100*(1-confidence)/2,100*(1-(1-confidence)/2)])
    return con_max 

def calcula_mean(linha):
    a = sum(linha)
    tamanho = len(linha)
    return a/tamanho

def calcula_std(linha):
    mean = calcula_mean(linha)
    def map_linha(el):
        return (el - mean) ** 2
    
    s = sum(map(map_linha, linha))/(len(linha)-1)
    s = math.sqrt(s)
    return s

def get_d_cohen_a(data_e, data_c):
    # https://sci-hub.se/https://doi.org/10.1093/jpepsy/jsp004
    N = len(data_c)


    me = calcula_mean(data_e)
    mc = calcula_mean(data_c)
    SDe = calcula_std(data_e)
    SDc = calcula_std(data_c)

    
    mean_abs = abs(me - mc)
    sd_pooled = math.sqrt(((SDe**2) + (SDc**2))/2)
    ajust = (N - 3)/ (N - 2.25) * math.sqrt((N-2)/N)

    r_sd_0 = sd_pooled == 0
    if r_sd_0:
        return 0

    d_cohen = mean_abs/sd_pooled *ajust
    return d_cohen


def get_descritor_catalogo(data, categoria, descritor, r_medido, r_max):
    def cr_f_categoria(categoria):
        def filter_categoria(element):
            return element['categoria'] == categoria
        return filter_categoria
    
    def map_element(element):
        return lambda x: x[element]
#     def c_map(element):
#         return element['list_kappa_cat']
#     def c_map_2(element):
#         return element
    strin = ""
    if(r_max):
        strin = "list_kappa_cat_max"
    else:
        strin = "list_kappa_cat"

    saida = []
    if (r_medido):
        saida.append(list(filter(cr_f_categoria(categoria), data['medido'][strin]))[0])
        
    else:
        for item in data['varios_kappa']:
            saida.append(list(filter(cr_f_categoria(categoria), item[strin]))[0]) 
        
    
#     print(saida)
    saida = list(map(map_element(descritor), saida))
    
    return saida


def get_cate_medida(data, cat, r_max):
    def cre_fil_categoria(categoria):
        return lambda x: categoria == x['categoria']

    ls = []
    if r_max:
        ls = data['medido']['list_kappa_cat_max']
    else:
        ls = data['medido']['list_kappa_cat']
        
    saida = list(filter(cre_fil_categoria(cat), ls ))
    return saida[0]



def get_categoria_descritores(data):
    def get_data_descritor_catalogo(cat, descritor):
        
        amax = get_descritor_catalogo(data, cat, descritor, False, True)
        ames = get_descritor_catalogo(data, cat, descritor, False, False)
    
        # HOTFIX, por algum motivo vem nan numero do software.
        amax  = list(filter(lambda x: x!="nan", amax))
        ames  = list(filter(lambda x: x!="nan", ames))

        con_m   = confidence_percentil(ames)
        con_max = confidence_percentil(amax)
        d = get_d_cohen_a(amax, ames)

        # dados do medido.
    
        k = get_cate_medida(data, cat, False)[descritor]
        k_max = get_cate_medida(data, cat, True)[descritor]

        return ( k, k_max, con_m, con_max, d, ames, amax )


    ls_descritor = ['kappa', 'prevalencia', 'vies']
    d_descritor_cat = {}
    d_descritor_cat["ls_cat"] = data['ls_cat_txt']
    d_descritor_cat["ls_descritor"] = ls_descritor
    for i, cat in enumerate(data['ls_cat_txt'], 1):
        df_cat = {"cat": cat}
        for descritor in ls_descritor:
            df_d = {}
            df_d["descritor"] = descritor
            s = get_data_descritor_catalogo(cat, descritor)
            df_d["d_measured_m"] = s[0]
            df_d["d_measured_max"] = s[1]
            df_d["ci_m"] = s[2]
            df_d["ci_max"] = s[3]
            df_d["d"] = s[4]
            df_d["d_ls_m"] = s[5]
            df_d["d_ls_max"] = s[6]
            df_cat[descritor] = df_d

        d_descritor_cat[cat] = df_cat
    
    return d_descritor_cat


def get_catalogo_descritores(data):
    def get_descritor(descritor):
        dt =     get_descritores_max(False, data)
        dt_max = get_descritores_max(True, data)

        ames = dt[descritor]
        amax = dt_max[descritor]
        con_m   = confidence_percentil(ames)
        con_max = confidence_percentil(amax)
        d = get_d_cohen_a(amax, ames)


        k     = data['medido']["catalogo_var"][descritor]
        k_max = data['medido']["catalogo_var_max"][descritor]
        return ( k, k_max, con_m, con_max, d, ames, amax )
    
    ls_descritor = ['kappa', 'prevalencia', 'vies']
    df_cat = {"cat": "Catalog"}
    for descritor in ls_descritor:
        df_d = {}
        df_d["descritor"] = descritor
        s = get_descritor(descritor)
        df_d["d_measured_m"] = s[0]
        df_d["d_measured_max"] = s[1]
        df_d["ci_m"] = s[2]
        df_d["ci_max"] = s[3]
        df_d["d"] = s[4]
        df_d["d_ls_m"] = s[5]
        df_d["d_ls_max"] = s[6]
        df_cat[descritor] = df_d


    return df_cat


def get_descritores(data):
    categoria_d = get_categoria_descritores(data)
    catalogo_d  = get_catalogo_descritores(data)

    categoria_d["ls_cat"].append('Catalog')
    categoria_d["Catalog"] = catalogo_d
    return categoria_d


