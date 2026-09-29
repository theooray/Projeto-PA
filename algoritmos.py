
import pandas as pd
import matplotlib.pyplot as plt

tamanhos = [10, 100, 1000, 10000, 100000, 1000000]
tipos = ["crescente","decrescente","random"]

dados = []
for tipo in tipos:
  for tamanho in tamanhos:
    caminho = f"Arquivos/Shell Sort/Tempo/{tipo}/tempo_{tipo}_{tamanho}.txt"

    with open(caminho) as f:
        linhas = f.readlines()

    tempo_s = linhas[1].split(":")[1]
    tempo_s = float(tempo_s.strip())

    dados.append({
       "tipo": tipo,
       "tamanho": tamanho,
       "tempo": tempo_s
    })

df = pd.DataFrame(dados)

for tipo in tipos:
  subset = df[df["tipo"] == tipo]
  plt.plot(subset["tamanho"], subset["tempo"], marker='o', label=tipo)

plt.xlabel("Tamanho da entrada")
plt.ylabel("Tempo (s)")
plt.xscale("log")
plt.legend()
plt.savefig("grafico_shell_sort.pdf")

print(df.to_latex(index=False, float_format=lambda x: f"{x:.8f}"))