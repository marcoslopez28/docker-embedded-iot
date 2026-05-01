import matplotlib.pyplot as plt
import random

# Generar datos simulados
dias = ["Lun", "Mar", "Mié", "Jue", "Vie"]
valores = [random.randint(1, 10) for _ in dias]

plt.figure()
plt.plot(dias, valores, marker="o")
plt.title("Datos simulados de sensor (IoT)")
plt.xlabel("Días")
plt.ylabel("Lectura")
plt.grid(True)

plt.savefig("output/grafico.png")

print("Gráfico generado correctamente en output/grafico.png")
