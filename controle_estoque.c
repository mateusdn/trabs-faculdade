#include <stdio.h>    // biblioteca entrada e saida
#include <string.h>   // biblioteca de manipula��o de strings
#include <stdlib.h>	  // biblioteca que fornece fun��es relacionadas � aloca��o de mem�ria


typedef struct {
    int codigo;
    char descricao[50];					// Define a estrutura Produto, que cont�m informa��es sobre o produto.
    int qtdEstoque;
    float preco;
} Produto;

typedef struct {
    int codigo;							// Define a estrutura ItemPedido, que cont�m informa��es sobre um item do pedido.
    int quantidade;
} ItemPedido;


int main() {      // Fun��o principal do programa //
    int opcao;
    int tamanho = 10;
    int qtdProdutos = 0;
    Produto *p = (Produto *)malloc(tamanho * sizeof(Produto));   // Aloca dinamicamente um array de Produto com o tamanho inicial especificado.

    while (1) {											// Loop infinito do Menu.
    system("cls");
        printf("\nMENU:\n\n");
        printf("1) GERENCIAR PRODUTOS\n");
        printf("2) REGISTRAR COMPRA\n");
        printf("0) FECHAR PROGRAMA\n");
        printf("\nESCOLHA UMA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {                                                      // In�cio do switch-case
            case 1:															  // Caso a op��o seja 1, chama a fun��o gerenciarProdutos para gerenciar os produtos no estoque.
                gerenciarProdutos(&p, &tamanho, &qtdProdutos);
                break;
            case 2:															  //  Caso a op��o seja 2, chama a fun��o registrarPedido para registrar um pedido de compra.
                registrarPedido(p, qtdProdutos);					  // Chama a fun��o registrarPedido, passando os produtos e a quantidade de produtos como par�metros.
                break;
            case 0:
                free(p);												  // libera a mem�ria alocada para o array de produtos, liberarando a mem�ria que foi previamente alocada dinamicamente usando malloc
                return 0;
            default:
                printf("OPCAO INVALIDA\n");
        }
    }
}

// MENU GERENCIAR PRODUTO //

void gerenciarProdutos(Produto **p, int *tamanho, int *qtdProdutos) {
    int opcao;
	system("cls");
    while (1) {									// Loop cont�nuo para exibir o menu e gerenciar produtos			
        printf("\nGERENCIAR PRODUTOS:\n");		
        printf("1) INCLUIR\n");
        printf("2) ALTERAR\n");
        printf("3) EXCLUIR\n");
        printf("4) CONSULTAR\n");
        printf("5) LISTAR\n");
        printf("0) VOLTAR\n");
        printf("ESCOLHA UMA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirProduto(p, tamanho, qtdProdutos);	// Chama a fun��o para incluir um produto		
                break;
            case 2:
                alterarProduto(*p, *qtdProdutos);			 // Chama a fun��o para alterar um produto
                break;
            case 3:
                excluirProduto(p, tamanho, qtdProdutos);	// Chama a fun��o para excluir um produto
                break;
            case 4:
                consultarProduto(*p, *qtdProdutos);			// Chama a fun��o para consultar um produto
                break;
            case 5:
                listarProdutos(*p, *qtdProdutos);			// Chama a fun��o para listar todos os produtos
                break;
            case 0:													// Retorna para a fun��o chamadora
                return;
            default:
                printf("OPCAO INVALIDA!\n");						// Op��o inv�lida
        }
    }
}


// MENU CARRINHO DE COMPRAS //

void registrarPedido(Produto *p, int qtdProdutos) {
    int opcao;																			// Vari�vel para armazenar a op��o escolhida pelo usu�rio
    int qtd_carrinho = 0;																// Vari�vel para armazenar a quantidade de itens no carrinho
    ItemPedido *carrinho = (ItemPedido *)malloc(qtdProdutos * sizeof(ItemPedido)); 	// Aloca mem�ria dinamicamente para o carrinho com base na quantidade de produtos dispon�veis

    while (1) {																			 // La�o principal para o registro do pedido
    
        printf("\nREGISTRAR COMPRA:\n");
        printf("1) ADICIONAR PRODUTO AO CARRINHO\n");
        printf("2) EXCLUIR PRODUTO DO CARRINHO\n");
        printf("3) CONSULTAR CARRINHO\n");
        printf("4) FINALIZAR COMPRA\n");
        printf("0) VOLTAR\n");
        printf("ESCOLHA UMA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                adicionarAoCarrinho(&carrinho, &qtd_carrinho, p, qtdProdutos);	// Chama a fun��o adicionarAoCarrinho passando os par�metros.
                break;
            case 2:
                excluirDoCarrinho(&carrinho, &qtd_carrinho);							// Chama a fun��o excluirDoCarrinho passando os par�metros.
                break;
            case 3:
                consultarCarrinho(carrinho, qtd_carrinho, p, qtdProdutos);		// Chama a fun��o consultarCarrinho passando os par�metros.
                break;
            case 4:
                finalizarCompra(&carrinho, &qtd_carrinho, p, qtdProdutos);		// Chama a fun��o finalizarCompra passando os par�metros.
                break;
            case 0:
                free(carrinho); 														// Libera a mem�ria alocada para o carrinho.
                return;
            default:
                printf("OPCAO INVALIDA!\n");											// Op��o inv�lida.
        }
    }
}


// FUN��ES DO PROGRAMA //

// FUN��O DE INCLUIR PRODUTO //


void incluirProduto(Produto **p, int *tamanho, int *qtdProdutos) {			// Verifica se a quantidade atual de produtos � igual ao tamanho do array
    if (*qtdProdutos == *tamanho) {   												
        *tamanho *= 2;																// Se for igual, dobra o tamanho do array
        *p = (Produto *)realloc(*p, *tamanho * sizeof(Produto));		// Realoca a mem�ria do array para o novo tamanho
    }

    Produto novo_produto;							// Cria uma vari�vel para armazenar o novo produto
    printf("CODIGO: ");								
    scanf("%d", &novo_produto.codigo);				// Solicita ao usu�rio o c�digo do produto
    printf("DESCRICAO: ");
    getchar();										// Limpa o buffer do teclado
    fgets(novo_produto.descricao, 100, stdin);   	// Solicita ao usu�rio a descri��o do produto
    printf("QUANTIDADE EM ESTOQUE: ");				// Solicita ao usu�rio a quantidade em estoque do produto
    scanf("%d", &novo_produto.qtdEstoque);
    printf("PRECO: ");								// Solicita ao usu�rio o pre�o do produto
    scanf("%f", &novo_produto.preco);  				

    (*p)[*qtdProdutos] = novo_produto;		// Adiciona o novo produto � posi��o atual do array de produtos
    (*qtdProdutos)++;								// Incrementa o contador de quantidade de produtos
}

// FUN��O DE ALTERAR PRODUTO //

void alterarProduto(Produto *p, int qtdProdutos) {			// Vari�vel para armazenar o c�digo do produto a ser alterado
    int codigo;
    printf("DIGITE O CODIGO DO PRODUTO PARA ALTERAR: ");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdProdutos; i++){ 						// Itera sobre os produtos existentes
        if (p[i].codigo == codigo) {							// Verifica se o c�digo do produto atual � igual ao c�digo fornecido pelo usu�rio
            printf("DESCRICAO: ");									// Se for igual, solicita ao usu�rio a nova descri��o do produto
            getchar();
            fgets(p[i].descricao, 100, stdin);
            printf("QUANTIDADE NO ESTOQUE: ");						// Solicita ao usu�rio a nova quantidade em estoque do produto
            scanf("%d", &p[i].qtdEstoque);
            printf("PRECO: ");										// Solicita ao usu�rio o novo pre�o do produto
            scanf("%f", &p[i].preco);
            return;												
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUN��O DE EXCLUIR PRODUTO //

void excluirProduto(Produto **p, int *tamanho, int *qtdProdutos) {
    int codigo;																	// Vari�vel para armazenar o c�digo do produto a ser exclu�do
    printf("DIGITE O CODIGO DO PRODUTO PARA EXCLUIR: ");					// Solicita ao usu�rio o c�digo do produto que deseja excluir
    scanf("%d", &codigo);

    for (int i = 0; i < *qtdProdutos; i++) {									// Itera sobre os produtos existentes
        if ((*p)[i].codigo == codigo) {									// Verifica se o c�digo do produto atual � igual ao c�digo fornecido pelo usu�rio
            for (int j = i; j < *qtdProdutos - 1; j++) {						// Se for igual, move todos os produtos seguintes uma posi��o para tr�s, sobrescrevendo o produto que est� sendo exclu�do.
                (*p)[j] = (*p)[j + 1];
            }
            (*qtdProdutos)--;													// Decrementa a quantidade de produtos existentes
            return;															
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUN��O DE CONSULTAR PRODUTO //

void consultarProduto(Produto *p, int qtdProdutos) {					// Vari�vel para armazenar o c�digo do produto a ser consultado
    int codigo;
    printf("DIGITE O CODIGO DO PRODUTO PARA CONSULTAR: ");				// Solicita ao usu�rio o c�digo do produto que deseja consultar
    scanf("%d", &codigo);

    for (int i = 0; i < qtdProdutos; i++) {									// Itera sobre os produtos existentes
        if (p[i].codigo == codigo) {										// Verifica se o c�digo do produto atual � igual ao c�digo fornecido pelo usu�rio
            printf("DESCRICAO: %s", p[i].descricao);						// Se for igual, imprime as informa��es do produto encontrado
            printf("QUANTIDADE NO ESTOQUE: %d\n", p[i].qtdEstoque);
            printf("PRECO: %.2f\n", p[i].preco);
            return;
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUN��O DE LISTAR PRODUTOS //

void listarProdutos(Produto *p, int qtdProdutos) {
    for (int i = 0; i < qtdProdutos; i++) {									// Itera sobre os produtos existentes
        printf("CODIGO: %d\n", p[i].codigo);								// Imprime o c�digo do produto
        printf("DESCRICAO: %s", p[i].descricao);							// Imprime a descri��o do produto
        printf("QUANTIDADE EM ESTOQUE: %d\n", p[i].qtdEstoque);			// Imprime a quantidade em estoque do produto
        printf("PRECO: %.2f\n\n", p[i].preco);							// Imprime o pre�o do produto
    }
}

// FUN��O DE ADICIONAR AO CARRINHO //

void adicionarAoCarrinho(ItemPedido **carrinho, int *qtd_carrinho, Produto *p, int qtdProdutos) {
    int codigo_produto;
    int quantidade;

    printf("DIGITE O CODIGO DO PRODUTO: ");							// Solicita ao usu�rio o c�digo do produto e a quantidade desejada
    scanf("%d", &codigo_produto);
    printf("DIGITE A QUANTIDADE: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < qtdProdutos; i++) {						// Percorre a lista de produtos
        if (p[i].codigo == codigo_produto) {					// Verifica se o c�digo do produto corresponde ao produto atual
            if (quantidade > p[i].qtdEstoque) {				// Verifica se a quantidade desejada est� dispon�vel em estoque
                printf("SEM ESTOQUE!\n");
                return;
            }

            (*carrinho)[*qtd_carrinho].codigo = codigo_produto; 	 // Adiciona o produto ao carrinho
            (*carrinho)[*qtd_carrinho].quantidade = quantidade;
            (*qtd_carrinho)++;

            p[i].qtdEstoque -= quantidade;					// Reduz a quantidade em estoque do produto

            printf("PRODUTO ADICIONADO AO CARRINHO!\n");
            return;
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUN��O DE EXCLUIR DO CARRINHO //

void excluirDoCarrinho(ItemPedido **carrinho, int *qtd_carrinho) {
    int codigo_produto;															// Declara��o da vari�vel para armazenar o c�digo do produto a ser removido do carrinho
    printf("DIGITE O CODIGO DO PRODUTO QUE DESEJA EXCLUIR DO CARRINHO: ");
    scanf("%d", &codigo_produto);												// Solicita ao usu�rio que digite o c�digo do produto a ser removido do carrinho e armazena na vari�vel

    for (int i = 0; i < *qtd_carrinho; i++) {									// Loop para percorrer o carrinho de compras
        if ((*carrinho)[i].codigo == codigo_produto) {							// Verifica se o c�digo do produto atual � igual ao c�digo do produto a ser exclu�do
                        for (int j = i; j < *qtd_carrinho - 1; j++) {			// Loop para deslocar os elementos do carrinho uma posi��o para tr�s, a partir da posi��o do produto a ser exclu�do
                (*carrinho)[j] = (*carrinho)[j + 1];							// Copia o elemento seguinte para a posi��o atual
            }
            (*qtd_carrinho)--;													// Reduz a quantidade total de itens no carrinho
            printf("PRODUTO REMOVIDO DO CARRINHO!\n");
            return;
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUN��O DE CONSULTAR O CARRINHO //

void consultarCarrinho(ItemPedido *carrinho, int qtd_carrinho, Produto *p, int qtdProdutos) {		// Fun��o para consultar o carrinho de compras
    printf("CARRINHO DE COMPRAS:\n");
    for (int i = 0; i < qtd_carrinho; i++) {								// Loop para percorrer os itens do carrinho
        int codigo_produto = carrinho[i].codigo;							// Obt�m o c�digo do produto do item atual do carrinho
        int quantidade = carrinho[i].quantidade;							// Obt�m a quantidade do produto do item atual do carrinho

        for (int j = 0; j < qtdProdutos; j++) {							// Loop para buscar o produto correspondente no vetor de produtos
            if (p[j].codigo == codigo_produto) {						// Verifica se o c�digo do produto atual � igual ao c�digo do produto do carrinho
                printf("PRODUTO: %s", p[j].descricao);				// Imprime a descri��o do produto
                printf("QUANTIDADE: %d\n", quantidade);						// Imprime a quantidade do produto no carrinho
                printf("PRECO UNITARIO: %.2f\n", p[j].preco);		// Imprime o pre�o unit�rio do produto
                float subtotal = quantidade * p[j].preco;			// Calcula o subtotal multiplicando a quantidade pelo pre�o unit�rio
                printf("SUBTOTAL: %.2f\n\n", subtotal);						// Imprime o subtotal do item do carrinho
                break;						
            }
        }
    }
}

// FUN��O DE DEBITAR O ESTOQUE //

void debitarEstoque(ItemPedido *carrinho, int qtd_carrinho, Produto *p, int qtdProdutos) {		// Fun��o para debitar a quantidade de produtos do estoque com base nos itens do carrinho
    for (int i = 0; i < qtd_carrinho; i++) {				// Loop para percorrer os itens do carrinho
        int codigo_produto = carrinho[i].codigo;			// Obt�m o c�digo do produto do item atual do carrinho
        int quantidade = carrinho[i].quantidade;			// Obt�m a quantidade do produto do item atual do carrinho

        for (int j = 0; j < qtdProdutos; j++) {			// Loop para buscar o produto correspondente no vetor de produtos
            if (p[j].codigo == codigo_produto) {		// Verifica se o c�digo do produto atual � igual ao c�digo do produto do carrinho
                p[j].qtdEstoque -= quantidade;		// Debita a quantidade do produto do estoque
                break;
            }
        }
    }
}

// FUN��O DE FINALIZAR A COMPRA //

void finalizarCompra(ItemPedido **carrinho, int *qtd_carrinho, Produto *p, int qtdProdutos) { 		// Fun��o para finalizar a compra, calculando o total a pagar
    float total = 0.0;																					// Vari�vel para armazenar o total a pagar, inicializada como 0.0

    printf("CARRINHO DE COMPRAS:\n");
    for (int i = 0; i < *qtd_carrinho; i++) {								// Loop para percorrer os itens do carrinho
        int codigo_produto = (*carrinho)[i].codigo;							// Obt�m o c�digo do produto do carrinho atual
        int quantidade = (*carrinho)[i].quantidade;							// Obt�m a quantidade do produto no carrinho atual

        for (int j = 0; j < qtdProdutos; j++) {							// Loop para procurar o produto correspondente na lista de produtos
            if (p[j].codigo == codigo_produto) {						// Verifica se o c�digo do produto coincide com o do carrinho
                printf("PRODUTO: %s", p[j].descricao);				// Imprime a descri��o do produto
                printf("QUANTIDADE: %d\n", quantidade);						// Imprime a quantidade do produto no carrinho
                printf("PRECO UNITARIO: %.2f\n", p[j].preco);		// Imprime o pre�o unit�rio do produto
                float subtotal = quantidade * p[j].preco;			// Calcula o subtotal para o produto no carrinho atual
                printf("SUBTOTAL: %.2f\n\n", subtotal);						// Imprime o subtotal para o produto no carrinho atual
                total += subtotal;											// Adiciona o subtotal ao total da compra
                break;
            }
        }
    }

    printf("TOTAL: %.2f\n", total);		// Imprime o valor total da compra com duas casas decimais
    printf("O NUMERO DO SEU PEDIDO E: %p\n", total); 

    debitarEstoque(*carrinho, *qtd_carrinho, p, qtdProdutos);	// Chama a fun��o debitarEstoque para atualizar o estoque dos produtos

    free(*carrinho);					
    *carrinho = NULL;		// Limpa o carrinho
    *qtd_carrinho = 0;

    printf("COMPRA FINALIZADA!\n");
}



