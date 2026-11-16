# 📦 Controle de Estoque em C

Sistema simples e eficiente de controle de estoque via terminal, desenvolvido em **linguagem C**. O projeto garante a persistência dos dados gravando e atualizando as informações diretamente em arquivos de texto locais.

## 🚀 Funcionalidades

* **Adicionar Item:** Cadastra novos produtos com nome composto e quantidade, ou soma automaticamente ao saldo caso o item já exista no estoque.
* **Remover / Dar Baixa:** Subtrai unidades de um produto existente, valida se há saldo disponível e remove o item automaticamente do arquivo caso a quantidade chegue a zero.
* **Listar Estoque:** Exibe todos os produtos cadastrados e suas respectivas quantidades em tempo real.
* **Persistência Segura:** Utiliza manipulação de arquivos (`fopen`, `fgets`, `fprintf`, `rename`) com arquivo temporário (`.tmp`) para evitar perda ou corrupção de dados durante atualizações.

## 🛠️ Tecnologias e Conceitos Aplicados

* Linguagem C (`stdio.h`, `stdlib.h`, `string.h`)
* Manipulação de arquivos de texto e arquivos temporários
* Tratamento de strings (`fgets`, `strcmp`, `strcspn`)
* Limpeza de buffer de entrada (`stdin`)

## 💻 Como compilar e executar

Certifique-se de ter um compilador C (como o **GCC**) instalado na sua máquina.

1. Clone este repositório ou baixe o arquivo `Controle_Estoque.c`.
2. Abra o terminal na pasta do arquivo e compile o código:
   ```bash
   gcc Controle_Estoque.c -o controle_estoque
   ```
3. Execute o programa gerado:
   * **No Windows:**
     ```bash
     controle_estoque.exe
     ```
   * **No Linux / macOS:**
     ```bash
     ./controle_estoque
     ```

## 📄 Licença

Este projeto está sob a licença **MIT**. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
