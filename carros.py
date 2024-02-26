class Carros:

    def __init__(self,marca,modelo,ano,cor):  #ATRIBUTOS DA CLASSE CARROS
        self.marca = marca
        self.modelo = modelo
        self.ano = ano
        self.cor = cor

carro_1 = Carros("Chevrolet","Opala","1978","Preto")    #ATRIBUTOS DO CARRO 1
carro_2 = Carros("Ford","Mustang","1969","Vermelho")    #ATRIBUTOS DO CARRO 2   
carro_3 = Carros("Nissan","GT-R","2005","Azul")         #ATRIBUTOS DO CARRO 3


#============
print('CATALOGO ~ CARROS ANTIGOS ~')
print('TEMOS 3 CARROS DISPONIVEIS!')
print('==============================')
print('(1) - VER CARRO 1 DISPONIVEL')
print('(2) - VER CARRO 2 DISPONIVEL')
print('(3) - VER CARRO 3 DISPONIVEL')
print('==============================')

#MENU
menu = int(input(""))

if menu == 1:  #MOSTRA OS ATRIBUTOS DO CARRO 1
    print(carro_1.marca, carro_1.modelo, carro_1.ano, carro_1.cor)

elif menu == 2: #MOSTRA OS ATRIBUTOS DO CARRO 2
    print(carro_2.marca, carro_2.modelo, carro_2.ano, carro_2.cor)

elif menu == 3: #MOSTRA OS ATRIBUTOS DO CARRO 3
    print(carro_3.marca, carro_3.modelo, carro_3.ano, carro_3.cor)

else: #FINALIZA O PROGRAMA
    print('OPCAO INVALIDA')