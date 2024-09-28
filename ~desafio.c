#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>   // Para suporte a acentuação
#include <math.h>

// Função que calcula o valor com base nos coeficientes fornecidos
int func_val(int x, int b) {
    // Coeficientes da fórmula
    double a0 = 186.752, a1 = -148.235, a2 = 34.5049, a3 = -3.5091;
    double a4 = 0.183166, a5 = -0.00513554, a6 = 0.0000735464, a7 = -4.22038e-7;

    // Cálculo polinomial com a variável b influenciando a constante a1
    double resultado = a0 + (a1 + b) * x + a2 * pow(x, 2) + a3 * pow(x, 3) +
                       a4 * pow(x, 4) + a5 * pow(x, 5) + a6 * pow(x, 6) + a7 * pow(x, 7);

    // Retorna o resultado arredondado para inteiro
    return (int)resultado;
}

int main() {
    setlocale(LC_ALL, "");  // Ativa o suporte a acentuação com base no sistema operacional

    // Variáveis para controle do laço e armazenamento de dados
    int quantidade, i, tamanho, j, decimal, b;
    char hexadecimal[101];  // Array para armazenar a mensagem hexadecimal
    char dupla[3] = "00";   // Usado para armazenar dois caracteres hexadecimais

    // Recebe a quantidade de mensagens que o usuário quer decifrar
    printf("Quantas mensagens voce quer decifrar? ");
    scanf("%d", &quantidade);

    // Laço para processar múltiplas mensagens
    for (i = 0; i < quantidade; i++) {
        // Entrada da mensagem hexadecimal
        printf("Digite a mensagem hexadecimal a ser codificada: ");
        scanf("%s", hexadecimal);

        // Entrada do valor da variável 'b'
        printf("Digite a variavel b: ");
        scanf("%d", &b);

        // Calcula o comprimento da mensagem hexadecimal
        tamanho = strlen(hexadecimal);

        // Laço para processar a mensagem hexadecimal em blocos de 2 caracteres
        for (j = 0; j < tamanho; j += 2) {
            // Evita acessar fora dos limites do array
            if (j + 1 >= tamanho) {
                break;
            }

            // Copia dois caracteres da string hexadecimal para 'dupla'
            dupla[0] = hexadecimal[j];
            dupla[1] = hexadecimal[j+1];

            // Verifica se encontrou "00" (indicando fim da mensagem)
            if (strcmp(dupla, "00") == 0) {
                break;
            }

            // Converte a dupla de caracteres hexadecimais para decimal
            decimal = strtol(dupla, NULL, 16);

            // Verifica se o caractere decimal é imprimível (evita caracteres de controle)
            if ((decimal >= 32 && decimal <= 126) || (decimal >= 160 && decimal <= 255)) {
                // Verifica o valor da função, se não for zero, imprime o caractere
                if (func_val(j, b) != 0) {
                    printf("%c", decimal);  // Exibe o caractere decodificado
                }
            }
        }

        // Pula uma linha após decifrar cada mensagem
        printf("\n\n");
    }

    return 0;
}
