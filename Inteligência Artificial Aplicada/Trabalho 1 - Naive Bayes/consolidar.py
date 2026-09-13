# -*- coding: utf-8 -*-
# Junta as tres bases de comentarios (IMDb, Amazon e Yelp) em um unico .arff
# para abrir no Weka, descartando as linhas que vierem quebradas.
# Rodar com: python3 consolidar.py

import os
import sys

# os tres .txt originais da UCI precisam estar na mesma pasta do script
BASE = os.path.dirname(os.path.abspath(__file__))
ENTRADA = BASE
SAIDA = os.path.join(BASE, "comentarios.arff")
CSV = os.path.join(BASE, "comentarios.csv")

ARQUIVOS = [
    ("imdb_labelled.txt", "imdb"),
    ("amazon_cells_labelled.txt", "amazon"),
    ("yelp_labelled.txt", "yelp"),
]


def escapar(texto):
    # dentro de aspas simples o arff exige escapar a barra e a propria aspa
    texto = texto.replace("\\", "\\\\")
    texto = texto.replace("'", "\\'")
    texto = texto.replace("\t", " ")
    return texto


def limpar(caminho, fonte, log):
    # le um arquivo e devolve so as linhas que dao para usar
    validos = []
    numero = 0
    for linha in open(caminho, encoding="utf-8"):
        numero += 1
        bruta = linha.rstrip("\n").rstrip("\r")

        if not bruta.strip():
            log.append((fonte, numero, "linha vazia", bruta))
            continue

        # sem a tabulacao nao da para saber onde termina o comentario
        if "\t" not in bruta:
            log.append((fonte, numero, "sem separador", bruta))
            continue

        partes = bruta.split("\t")
        comentario = "\t".join(partes[:-1]).strip()
        classe = partes[-1].strip()

        if comentario == "":
            log.append((fonte, numero, "comentario vazio", bruta))
            continue

        # aceita so 0 e 1, qualquer outra coisa e registro nao classificado
        if classe not in ("0", "1"):
            log.append((fonte, numero, "classe invalida ou ausente", bruta))
            continue

        # varias frases do imdb terminam com espacos sobrando
        comentario = " ".join(comentario.split())
        validos.append((comentario, classe))
    return validos


def main():
    faltando = [n for n, _ in ARQUIVOS if not os.path.exists(os.path.join(ENTRADA, n))]
    if faltando:
        sys.exit("Faltam os arquivos originais nesta pasta: " + ", ".join(faltando))

    registros = []
    log = []
    for nome, fonte in ARQUIVOS:
        lidos = limpar(os.path.join(ENTRADA, nome), fonte, log)
        print("%-28s %4d registros validos" % (nome, len(lidos)))
        registros.extend(lidos)

    negativos = sum(1 for _, c in registros if c == "0")
    positivos = len(registros) - negativos

    # so para saber quantos comentarios aparecem repetidos na base
    vistos = {}
    repetidos = 0
    conflitos = 0
    for comentario, classe in registros:
        chave = comentario.lower()
        if chave in vistos:
            repetidos += 1
            if vistos[chave] != classe:
                conflitos += 1
        else:
            vistos[chave] = classe

    with open(SAIDA, "w", encoding="utf-8") as arq:
        arq.write("% Comentarios de IMDb, Amazon e Yelp (Sentiment Labelled\n")
        arq.write("% Sentences - UCI Machine Learning Repository).\n")
        arq.write("% 0 = comentario negativo, 1 = comentario positivo.\n\n")
        arq.write("@relation comentarios\n\n")
        arq.write("@attribute comentario string\n")
        arq.write("@attribute classe {0,1}\n\n")
        arq.write("@data\n")
        for comentario, classe in registros:
            arq.write("'%s',%s\n" % (escapar(comentario), classe))

    # o csv nao e usado pelo Weka, serve para conferir a base no editor
    with open(CSV, "w", encoding="utf-8") as arq:
        arq.write("comentario\tclasse\n")
        for comentario, classe in registros:
            arq.write("%s\t%s\n" % (comentario.replace("\t", " "), classe))

    if log:
        caminho_log = os.path.join(BASE, "registros_descartados.txt")
        with open(caminho_log, "w", encoding="utf-8") as arq:
            for fonte, numero, motivo, bruta in log:
                arq.write("%s linha %d - %s - %s\n" % (fonte, numero, motivo, bruta))

    print("")
    print("registros na base final .. %d" % len(registros))
    print("negativos (0) ........... %d" % negativos)
    print("positivos (1) ........... %d" % positivos)
    print("descartados ............. %d" % len(log))
    print("comentarios repetidos ... %d (com classe divergente: %d)" % (repetidos, conflitos))
    print("arquivo gerado .......... %s" % SAIDA)


if __name__ == "__main__":
    main()
