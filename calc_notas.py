import os

print('=================')   
print('CALCULADORA NOTAS')
print('=================')
print('(1) NOTA A1')
print('(2) NOTA A2')
print('(3) SAIR')
print('=================')

#VARIAVEIS

menu = int(input(""))  
a1 = 1
a2 = 1


# MENU DO PROGRAMA
if menu == 1: 
    ava1 = float(input('DIGITE SUA NOTA AVA1: (ENTRE 0 E 10): '))
    ava2 = float(input('DIGITE SUA NOTA AVA2: (ENTRE 0 E 10): '))
    
    
    if ava1 and ava2 <=10:
        print('SUA MEDIA DA A1 E: ')
        (print((ava1 + ava2) / 2)) #CALCULO MEDIA A1
    else:
        print('OPCAO INVALIDA')
        
        
elif menu == 2:
    if a1 and a2 <=10:
        a1 = float(input('DIGITE SUA NOTA A1 (ENTRE 0 - 10): '))
        a2 = float(input('DIGITE SUA NOTA A2 (ENTRE 0 - 10): '))
        print('SUA MEDIA FINAL E: ')
        media_final = (a1 * 0.4) + (a2 * 0.6) #CALCULO MEDIA A2
        print(media_final)
    else:
        print('OPCAO INVALIDA')
    
# FINALIZA O PROGRAMA
elif menu == 3: 
    print('Programa Finalizado')
    exit()
