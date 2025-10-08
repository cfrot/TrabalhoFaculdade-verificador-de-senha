# Verificador de Senha em C

## 📖 Sobre o Projeto

Este é um programa desenvolvido em Linguagem C como parte da avaliação da disciplina de Programação de Software Básico em C do curso de Ciência da computação na Estácio de Sá.

O objetivo do programa é validar uma senha digitada pelo usuário contra uma senha mestra armazenada em um arquivo, utilizando uma entrada de dados mascarada para proteger a digitação.

---

## ✨ Funcionalidades

O programa implementa os seguintes requisitos:

- **Leitura de Arquivo:** A senha correta é lida de um arquivo `senha.txt`.
- **Entrada Mascarada:** A senha digitada pelo usuário é substituída por asteriscos (`*`) no console.
- **Suporte a Backspace:** O usuário pode corrigir a digitação usando a tecla Backspace.
- **Portabilidade:** O código é compatível com ambientes Windows e Linux/Unix.
- **Tratamento de Erros:** Verifica a existência do arquivo `senha.txt` antes de prosseguir.

---

## 🚀 Como Executar

Para compilar e executar este projeto, siga os passos abaixo.

### Pré-requisitos

- É necessário ter um compilador C, como o **GCC**, instalado em sua máquina.

### Passos

1. **Clone o repositório:**
   ```bash
   git clone [https://github.com/cfrot/TrabalhoFaculdade-verificador-de-senha.git](https://github.com/cfrot/TrabalhoFaculdade-verificador-de-senha.git)
   cd TrabalhoFaculdade-verificador-de-senha
