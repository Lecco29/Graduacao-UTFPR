# Trabalho 1 - Naive Bayes no Weka

Classificação de comentários em positivo ou negativo usando o Naive Bayes do Weka,
sobre as bases de avaliações do IMDb, Amazon e Yelp (Sentiment Labelled Sentences,
UCI). As três fontes foram juntadas em uma base única de 3000 registros, 1500 de
cada classe.

## Arquivos

- `Relatorio - Trabalho 1 - Naive Bayes.pdf` - relatório entregue
- `comentarios.arff` - base consolidada e tratada, pronta para abrir no Weka
- `consolidar.py` - script que junta os três arquivos originais e gera o .arff

## Resultados com 10 folds

| Configuração | Acurácia | Kappa |
|---|---|---|
| Naive Bayes | 69,33% | 0,3867 |
| Naive Bayes com discretização supervisionada | 68,07% | 0,3613 |
| Naive Bayes Multinomial | 82,93% | 0,6587 |
| SMO | 81,03% | 0,6207 |
| J48 | 67,77% | 0,3553 |
| ZeroR (referência) | 50,00% | 0 |

No Weka: abrir o `comentarios.arff`, aplicar o filtro `StringToWordVector`, ir na aba
Classify e escolher `bayes.NaiveBayes`.

Os três arquivos originais (`imdb_labelled.txt`, `amazon_cells_labelled.txt` e
`yelp_labelled.txt`) não estão aqui porque são da UCI. Para rodar o `consolidar.py`,
baixe a base Sentiment Labelled Sentences e deixe os três na mesma pasta do script.
