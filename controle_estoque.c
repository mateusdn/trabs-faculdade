#include <stdio.h>    // biblioteca entrada e saida
#include <string.h>   // biblioteca de manipulação de strings
#include <stdlib.h>	  // biblioteca que fornece funções relacionadas à alocação de memória


typedef struct {
    int codigo;
    char descricao[50];					// Define a estrutura Produto, que contém informações sobre o produto.
    int qtdEstoque;
    float preco;
} Produto;

typedef struct {
    int codigo;							// Define a estrutura ItemPedido, que contém informações sobre um item do pedido.
    int quantidade;
} ItemPedido;


int main() {      // Função principal do programa //
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

        switch (opcao) {                                                      // Início do switch-case
            case 1:															  // Caso a opção seja 1, chama a função gerenciarProdutos para gerenciar os produtos no estoque.
                gerenciarProdutos(&p, &tamanho, &qtdProdutos);
                break;
            case 2:															  //  Caso a opção seja 2, chama a função registrarPedido para registrar um pedido de compra.
                registrarPedido(p, qtdProdutos);					  // Chama a função registrarPedido, passando os produtos e a quantidade de produtos como parâmetros.
                break;
            case 0:
                free(p);												  // libera a memória alocada para o array de produtos, liberarando a memória que foi previamente alocada dinamicamente usando malloc
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
    while (1) {									// Loop contínuo para exibir o menu e gerenciar produtos			
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
                incluirProduto(p, tamanho, qtdProdutos);	// Chama a função para incluir um produto		
                break;
            case 2:
                alterarProduto(*p, *qtdProdutos);			 // Chama a função para alterar um produto
                break;
            case 3:
                excluirProduto(p, tamanho, qtdProdutos);	// Chama a função para excluir um produto
                break;
            case 4:
                consultarProduto(*p, *qtdProdutos);			// Chama a função para consultar um produto
                break;
            case 5:
                listarProdutos(*p, *qtdProdutos);			// Chama a função para listar todos os produtos
                break;
            case 0:													// Retorna para a função chamadora
                return;
            default:
                printf("OPCAO INVALIDA!\n");						// Opção inválida
        }
    }
}


// MENU CARRINHO DE COMPRAS //

void registrarPedido(Produto *p, int qtdProdutos) {
    int opcao;																			// Variável para armazenar a opção escolhida pelo usuário
    int qtd_carrinho = 0;																// Variável para armazenar a quantidade de itens no carrinho
    ItemPedido *carrinho = (ItemPedido *)malloc(qtdProdutos * sizeof(ItemPedido)); 	// Aloca memória dinamicamente para o carrinho com base na quantidade de produtos disponíveis

    while (1) {																			 // Laço principal para o registro do pedido
    
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
                adicionarAoCarrinho(&carrinho, &qtd_carrinho, p, qtdProdutos);	// Chama a função adicionarAoCarrinho passando os parâmetros.
                break;
            case 2:
                excluirDoCarrinho(&carrinho, &qtd_carrinho);							// Chama a função excluirDoCarrinho passando os parâmetros.
                break;
            case 3:
                consultarCarrinho(carrinho, qtd_carrinho, p, qtdProdutos);		// Chama a função consultarCarrinho passando os parâmetros.
                break;
            case 4:
                finalizarCompra(&carrinho, &qtd_carrinho, p, qtdProdutos);		// Chama a função finalizarCompra passando os parâmetros.
                break;
            case 0:
                free(carrinho); 														// Libera a memória alocada para o carrinho.
                return;
            default:
                printf("OPCAO INVALIDA!\n");											// Opção inválida.
        }
    }
}


// FUNÇÕES DO PROGRAMA //

// FUNÇÃO DE INCLUIR PRODUTO //


void incluirProduto(Produto **p, int *tamanho, int *qtdProdutos) {			// Verifica se a quantidade atual de produtos é igual ao tamanho do array
    if (*qtdProdutos == *tamanho) {   												
        *tamanho *= 2;																// Se for igual, dobra o tamanho do array
        *p = (Produto *)realloc(*p, *tamanho * sizeof(Produto));		// Realoca a memória do array para o novo tamanho
    }

    Produto novo_produto;							// Cria uma variável para armazenar o novo produto
    printf("CODIGO: ");								
    scanf("%d", &novo_produto.codigo);				// Solicita ao usuário o código do produto
    printf("DESCRICAO: ");
    getchar();										// Limpa o buffer do teclado
    fgets(novo_produto.descricao, 100, stdin);   	// Solicita ao usuário a descrição do produto
    printf("QUANTIDADE EM ESTOQUE: ");				// Solicita ao usuário a quantidade em estoque do produto
    scanf("%d", &novo_produto.qtdEstoque);
    printf("PRECO: ");								// Solicita ao usuário o preço do produto
    scanf("%f", &novo_produto.preco);  				

    (*p)[*qtdProdutos] = novo_produto;		// Adiciona o novo produto à posição atual do array de produtos
    (*qtdProdutos)++;								// Incrementa o contador de quantidade de produtos
}

// FUNÇÃO DE ALTERAR PRODUTO //

void alterarProduto(Produto *p, int qtdProdutos) {			// Variável para armazenar o código do produto a ser alterado
    int codigo;
    printf("DIGITE O CODIGO DO PRODUTO PARA ALTERAR: ");
    scanf("%d", &codigo);

    for (int i = 0; i < qtdProdutos; i++){ 						// Itera sobre os produtos existentes
        if (p[i].codigo == codigo) {							// Verifica se o código do produto atual é igual ao código fornecido pelo usuário
            printf("DESCRICAO: ");									// Se for igual, solicita ao usuário a nova descrição do produto
            getchar();
            fgets(p[i].descricao, 100, stdin);
            printf("QUANTIDADE NO ESTOQUE: ");						// Solicita ao usuário a nova quantidade em estoque do produto
            scanf("%d", &p[i].qtdEstoque);
            printf("PRECO: ");										// Solicita ao usuário o novo preço do produto
            scanf("%f", &p[i].preco);
            return;												
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUNÇÃO DE EXCLUIR PRODUTO //

void excluirProduto(Produto **p, int *tamanho, int *qtdProdutos) {
    int codigo;																	// Variável para armazenar o código do produto a ser excluído
    printf("DIGITE O CODIGO DO PRODUTO PARA EXCLUIR: ");					// Solicita ao usuário o código do produto que deseja excluir
    scanf("%d", &codigo);

    for (int i = 0; i < *qtdProdutos; i++) {									// Itera sobre os produtos existentes
        if ((*p)[i].codigo == codigo) {									// Verifica se o código do produto atual é igual ao código fornecido pelo usuário
            for (int j = i; j < *qtdProdutos - 1; j++) {						// Se for igual, move todos os produtos seguintes uma posição para trás, sobrescrevendo o produto que está sendo excluído.
                (*p)[j] = (*p)[j + 1];
            }
            (*qtdProdutos)--;													// Decrementa a quantidade de produtos existentes
            return;															
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUNÇÃO DE CONSULTAR PRODUTO //

void consultarProduto(Produto *p, int qtdProdutos) {					// Variável para armazenar o código do produto a ser consultado
    int codigo;
    printf("DIGITE O CODIGO DO PRODUTO PARA CONSULTAR: ");				// Solicita ao usuário o código do produto que deseja consultar
    scanf("%d", &codigo);

    for (int i = 0; i < qtdProdutos; i++) {									// Itera sobre os produtos existentes
        if (p[i].codigo == codigo) {										// Verifica se o código do produto atual é igual ao código fornecido pelo usuário
            printf("DESCRICAO: %s", p[i].descricao);						// Se for igual, imprime as informações do produto encontrado
            printf("QUANTIDADE NO ESTOQUE: %d\n", p[i].qtdEstoque);
            printf("PRECO: %.2f\n", p[i].preco);
            return;
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUNÇÃO DE LISTAR PRODUTOS //

void listarProdutos(Produto *p, int qtdProdutos) {
    for (int i = 0; i < qtdProdutos; i++) {									// Itera sobre os produtos existentes
        printf("CODIGO: %d\n", p[i].codigo);								// Imprime o código do produto
        printf("DESCRICAO: %s", p[i].descricao);							// Imprime a descrição do produto
        printf("QUANTIDADE EM ESTOQUE: %d\n", p[i].qtdEstoque);			// Imprime a quantidade em estoque do produto
        printf("PRECO: %.2f\n\n", p[i].preco);							// Imprime o preço do produto
    }
}

// FUNÇÃO DE ADICIONAR AO CARRINHO //

void adicionarAoCarrinho(ItemPedido **carrinho, int *qtd_carrinho, Produto *p, int qtdProdutos) {
    int codigo_produto;
    int quantidade;

    printf("DIGITE O CODIGO DO PRODUTO: ");							// Solicita ao usuário o código do produto e a quantidade desejada
    scanf("%d", &codigo_produto);
    printf("DIGITE A QUANTIDADE: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < qtdProdutos; i++) {						// Percorre a lista de produtos
        if (p[i].codigo == codigo_produto) {					// Verifica se o código do produto corresponde ao produto atual
            if (quantidade > p[i].qtdEstoque) {				// Verifica se a quantidade desejada está disponível em estoque
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

// FUNÇÃO DE EXCLUIR DO CARRINHO //

void excluirDoCarrinho(ItemPedido **carrinho, int *qtd_carrinho) {
    int codigo_produto;															// Declaração da variável para armazenar o código do produto a ser removido do carrinho
    printf("DIGITE O CODIGO DO PRODUTO QUE DESEJA EXCLUIR DO CARRINHO: ");
    scanf("%d", &codigo_produto);												// Solicita ao usuário que digite o código do produto a ser removido do carrinho e armazena na variável

    for (int i = 0; i < *qtd_carrinho; i++) {									// Loop para percorrer o carrinho de compras
        if ((*carrinho)[i].codigo == codigo_produto) {							// Verifica se o código do produto atual é igual ao código do produto a ser excluído
                        for (int j = i; j < *qtd_carrinho - 1; j++) {			// Loop para deslocar os elementos do carrinho uma posição para trás, a partir da posição do produto a ser excluído
                (*carrinho)[j] = (*carrinho)[j + 1];							// Copia o elemento seguinte para a posição atual
            }
            (*qtd_carrinho)--;													// Reduz a quantidade total de itens no carrinho
            printf("PRODUTO REMOVIDO DO CARRINHO!\n");
            return;
        }
    }

    printf("PRODUTO NAO ENCONTRADO!\n");
}

// FUNÇÃO DE CONSULTAR O CARRINHO //

void consultarCarrinho(ItemPedido *carrinho, int qtd_carrinho, Produto *p, int qtdProdutos) {		// Função para consultar o carrinho de compras
    printf("CARRINHO DE COMPRAS:\n");
    for (int i = 0; i < qtd_carrinho; i++) {								// Loop para percorrer os itens do carrinho
        int codigo_produto = carrinho[i].codigo;							// Obtém o código do produto do item atual do carrinho
        int quantidade = carrinho[i].quantidade;							// Obtém a quantidade do produto do item atual do carrinho

        for (int j = 0; j < qtdProdutos; j++) {							// Loop para buscar o produto correspondente no vetor de produtos
            if (p[j].codigo == codigo_produto) {						// Verifica se o código do produto atual é igual ao código do produto do carrinho
                printf("PRODUTO: %s", p[j].descricao);				// Imprime a descrição do produto
                printf("QUANTIDADE: %d\n", quantidade);						// Imprime a quantidade do produto no carrinho
                printf("PRECO UNITARIO: %.2f\n", p[j].preco);		// Imprime o preço unitário do produto
                float subtotal = quantidade * p[j].preco;			// Calcula o subtotal multiplicando a quantidade pelo preço unitário
                printf("SUBTOTAL: %.2f\n\n", subtotal);						// Imprime o subtotal do item do carrinho
                break;						
            }
        }
    }
}

// FUNÇÃO DE DEBITAR O ESTOQUE //

void debitarEstoque(ItemPedido *carrinho, int qtd_carrinho, Produto *p, int qtdProdutos) {		// Função para debitar a quantidade de produtos do estoque com base nos itens do carrinho
    for (int i = 0; i < qtd_carrinho; i++) {				// Loop para percorrer os itens do carrinho
        int codigo_produto = carrinho[i].codigo;			// Obtém o código do produto do item atual do carrinho
        int quantidade = carrinho[i].quantidade;			// Obtém a quantidade do produto do item atual do carrinho

        for (int j = 0; j < qtdProdutos; j++) {			// Loop para buscar o produto correspondente no vetor de produtos
            if (p[j].codigo == codigo_produto) {		// Verifica se o código do produto atual é igual ao código do produto do carrinho
                p[j].qtdEstoque -= quantidade;		// Debita a quantidade do produto do estoque
                break;
            }
        }
    }
}

// FUNÇÃO DE FINALIZAR A COMPRA //

void finalizarCompra(ItemPedido **carrinho, int *qtd_carrinho, Produto *p, int qtdProdutos) { 		// Função para finalizar a compra, calculando o total a pagar
    float total = 0.0;																					// Variável para armazenar o total a pagar, inicializada como 0.0

    printf("CARRINHO DE COMPRAS:\n");
    for (int i = 0; i < *qtd_carrinho; i++) {								// Loop para percorrer os itens do carrinho
        int codigo_produto = (*carrinho)[i].codigo;							// Obtém o código do produto do carrinho atual
        int quantidade = (*carrinho)[i].quantidade;							// Obtém a quantidade do produto no carrinho atual

        for (int j = 0; j < qtdProdutos; j++) {							// Loop para procurar o produto correspondente na lista de produtos
            if (p[j].codigo == codigo_produto) {						// Verifica se o código do produto coincide com o do carrinho
                printf("PRODUTO: %s", p[j].descricao);				// Imprime a descrição do produto
                printf("QUANTIDADE: %d\n", quantidade);						// Imprime a quantidade do produto no carrinho
                printf("PRECO UNITARIO: %.2f\n", p[j].preco);		// Imprime o preço unitário do produto
                float subtotal = quantidade * p[j].preco;			// Calcula o subtotal para o produto no carrinho atual
                printf("SUBTOTAL: %.2f\n\n", subtotal);						// Imprime o subtotal para o produto no carrinho atual
                total += subtotal;											// Adiciona o subtotal ao total da compra
                break;
            }
        }
    }

    printf("TOTAL: %.2f\n", total);		// Imprime o valor total da compra com duas casas decimais
    printf("O NUMERO DO SEU PEDIDO E: %p\n", total); 

    debitarEstoque(*carrinho, *qtd_carrinho, p, qtdProdutos);	// Chama a função debitarEstoque para atualizar o estoque dos produtos

    free(*carrinho);					
    *carrinho = NULL;		// Limpa o carrinho
    *qtd_carrinho = 0;

    printf("COMPRA FINALIZADA!\n");
}



