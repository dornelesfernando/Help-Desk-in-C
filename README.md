<a id="readme-top"></a>

<img width="1916" height="875" alt="image" src="https://github.com/user-attachments/assets/bd4bc5a3-d1a0-47bd-83f6-c7c6582cdfff" />

<div align="center">
    
  ![https://img.shields.io/badge/status-em--desenvolvimento-blueviolet?style=for-the-badge](https://img.shields.io/badge/status-em--desenvolvimento-blueviolet?style=for-the-badge)
  [![License: Apache 2.0](https://img.shields.io/badge/License-Apache_2.0-blue.svg?style=for-the-badge)](https://opensource.org/licenses/Apache-2.0)
    
  ![https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
  ![https://img.shields.io/badge/GCC-0078D6?style=for-the-badge&logo=gcc&logoColor=white](https://img.shields.io/badge/GCC-0078D6?style=for-the-badge&logo=gcc&logoColor=white)
  ![https://img.shields.io/badge/Make-000000?style=for-the-badge&logo=gnu-make&logoColor=white](https://img.shields.io/badge/Make-000000?style=for-the-badge&logo=gnu-make&logoColor=white)
  ![Visual Studio Code](https://img.shields.io/badge/Visual_Studio-343A40?style=for-the-badge&logo=visual-studio&logoColor=white)
</div>

<h1 align="center">
    🖥️ System Help Desk em C 🖥️
</h1>

<p align="center">
  Um sistema de Help Desk baseado em terminal, implementado em C puro para a disciplina de Estrutura de Dados e Programação.
  <br />
  <a href="https://github.com/dornelesfernando/Help-Desk-in-C"><strong>Explore os Arquivos »</strong></a>
  <br />
  <br />
  <a href="#começando-ambiente-e-instalacao">Baixe, Configure e Execute</a>
  ·
  <a href="https://github.com/dornelesfernando/Help-Desk-in-C/issues/new?template=bug-report-%F0%9F%90%9B.md">Reportar Bug</a>
  ·
  <a href="https://github.com/dornelesfernando/Help-Desk-in-C/issues/new?template=feature-request-%E2%9C%A8.md">Sugerir Melhoria</a>
</p>

<a id="visao-geral-do-projeto"></a>
## 🔎 Visão Geral do Projeto

O **System Help Desk em C** é um projeto acadêmico desenvolvido para a disciplina de Estrutura de Dados e Programação. O objetivo é aplicar conceitos fundamentais de programação em C e estruturas de dados complexas para simular um sistema de gerenciamento de chamados de T.I..

O sistema **não utiliza banco de dados**; toda a gestão de dados é feita em memória durante a execução, com os dados sendo gerenciados por estruturas alocadas dinamicamente.

O núcleo do projeto é a implementação de um sistema de atendimento que utiliza duas filas distintas para garantir a eficiência e a ordem correta do atendimento, simulando um ambiente de suporte técnico real:

- **Fila de Prioridade (Max-Heap):** Utilizada para gerenciar chamados de prioridade `URGENTE`, `ALTA` e `MEDIA`. Isso garante que, independentemente da ordem de chegada, os chamados mais críticos sejam sempre "puxados" para o topo e atendidos primeiro.
- **Fila Comum (FIFO - First-In, First-Out):** Utilizada para gerenciar chamados de prioridade `BAIXA`. Isso assegura um atendimento justo, baseado na ordem de chegada, para problemas não-críticos.

O fluxo de atendimento do administrador sempre verifica a Fila de Prioridade (Heap) primeiro. Somente quando ela está vazia, o sistema começa a processar a Fila Comum (FIFO).

---
<details open>
  <summary>📚 Tabela de Conteúdos</summary>
  <ol>
    <li><a href="#visao-geral-do-projeto">Visão Geral do Projeto</a></li>
    <li><a href="#funcionalidades-principais">Funcionalidades Principais</a></li>
    <li><a href="#estruturas-de-dados-utilizadas">Estruturas de Dados Utilizadas</a></li>
    <li><a href="#stack-de-tecnologias">Stack de Tecnologias</a></li>
    <li><a href="#começando-ambiente-e-instalacao">Começando: Ambiente e Instalação</a></li>
        <ol>
            <li><a href="#pre-requisitos-do-sistema">Pré-requisitos do Sistema</a></li>
            <li><a href="#guia-de-compilação-e-execução">Guia de Compilação e Execução</a></li>
        </ol>
    <li><a href="#como-usar-o-sistema">Como Usar o Sistema</a></li>
    <li><a href="#licenca">Licença</a></li>
    <li><a href="#autor">Autor</a></li>
    <li><a href="#agradecimentos">Agradecimentos</a></li>
  </ol>
</details>

---

<a id="funcionalidades-principais"></a>
## 📝 Funcionalidades Principais
A plataforma é dividida em módulos que cobrem as principais áreas de gestão de uma organização.

- **Interface de Terminal:** Menu principal interativo totalmente baseado em texto (TUI), com uso de cores para melhor usabilidade.
- **Abertura de Chamados:** Permite que usuários (clientes) abram novos chamados, preenchendo informações como nome, e-mail, título, descrição e nível de prioridade.
- **Login de Administrador:** Uma área restrita (atualmente com senha "hard-coded") permite o acesso ao menu de gerenciamento.
- **Atendimento de Chamados (Lógica de Negócio):** Administradores atendem chamados seguindo a regra de negócio estrita:
    1. Atender todos os chamados da **Heap de Prioridade** (Urgente/Alto/Médio).
    2. Apenas se a Heap estiver vazia, atender chamados da **Fila FIFO** (Baixo).
- **Listagem e Filtros:** Clientes e administradores podem listar todos os chamados cadastrados, com opções para filtrar por prioridade ou status.
- **Atualização de Chamados:** Clientes podem atualizar seus próprios chamados (se não estiverem fechados), e administradores podem atualizar qualquer chamado.
- **Sistema de Logs:** Um sistema de log dinâmico, implementado com `realloc`, registra todas as ações importantes do sistema, que podem ser visualizadas ao final da execução.

<a id="estruturas-de-dados-utilizadas"></a>
### 🌲 Estruturas de Dados Utilizadas
- **`struct`:** Usada extensivamente para definir os tipos de dados principais: `MainParams` (estado do sistema), `Call` (dados do ticket), `CallHeap` (fila de prioridade) e `CallFIFO` (fila comum).
- **Ponteiros e Alocação Dinâmica:** `malloc`, `realloc` e `free` são usados para gerenciar a memória dos chamados e das filas.
- **Fila de Prioridade (Max-Heap):** Implementada usando um array.
    - `heap_insert`: Adiciona um novo chamado e usa a função `tidying_up` (heapify-up) para manter a propriedade da heap.
- **Fila (FIFO):** Implementada usando um array circular com ponteiros `front` e `tail`.
    - `init_fifo`: Aloca memória para a fila e inicializa os índices.
    - `fifo_enqueue`: Adiciona um chamado ao final da fila (posição `tail`).

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="stack-de-tecnologias"></a>
## 🖥️ Stack de Tecnologias
A escolha da stack tecnológica foi orientada pela exigência da disciplina, focando em C puro e gerenciamento manual de memória.

<div align="center">

| Categoria     | Tecnologia                                                                                                                                                                                                                                                                                                     |
| ------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Linguagem** | ![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)                                                                                                                                                                                                                        |
| **Compilador**| ![GCC](https://img.shields.io/badge/GCC-0078D6?style=for-the-badge&logo=gcc&logoColor=white)                                                                                                                                                                                                                   |
| **Build** | ![Make](https://img.shields.io/badge/Make-000000?style=for-the-badge&logo=gnu-make&logoColor=white)                                                                                                                                                                                                            |
| **Editor** | ![Visual Studio Code](https://img.shields.io/badge/Visual_Studio-343A40?style=for-the-badge&logo=visual-studio&logoColor=white)                                                                                                                                                                                  |

</div>

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="começando-ambiente-e-instalacao"></a>
## ⚙️ Começando: Ambiente e Instalação
Esta seção fornece um guia para compilar e executar o projeto localmente.

<a id="pre-requisitos-do-sistema"></a>
### Pré-requisitos do Sistema
Antes de iniciar, certifique-se de que seu sistema possui as ferramentas de build essenciais do C.

- **Git:** Essencial para clonar o repositório.

<a id="guia-de-compilação-e-execução"></a>
### Guia de Compilação e Execução
Siga os passos abaixo para colocar o sistema em funcionamento.

#### Passo 1: Clonando e Configurando o Projeto
1.  No seu terminal, clone o repositório do projeto:
    {[git clone https://github.com/dornelesfernando/Help-Desk-in-C.git]}

#### Passo 2: Compilando o Sistema
1.  Abra o projeto em um compilador online como *Online GBD* ou outro compilador.

#### Passo 3: Executando o Sistema
1.  Após a compilação bem-sucedida, execute o programa

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="como-usar-o-sistema"></a>
## ▶️ Como Usar o Sistema
Após a execução, o sistema apresentará o menu principal no terminal. Siga as instruções na tela para navegar entre as opções.

**Menu do Cliente (Não-Logado):**
1.  **Abrir chamado:** Inicia o fluxo de criação de um novo ticket.
2.  **Atualizar chamado:** Permite ao cliente atualizar um chamado existente.
3.  **Ver todos os chamados:** Lista todos os chamados no sistema.
4.  **Ver lista de baixa prioridade (normal):** Mostra apenas chamados da fila FIFO.
5.  **Ver lista por prioridade e status:** Permite filtrar a visualização.
6.  **Ver último chamado aberto/atualizado:** Exibe os detalhes do último chamado criado nesta sessão.
7.  **Visualizar log's:** Mostra os logs do sistema.
8.  **Acessar menu do administrador:** Pede uma senha para logar.
9.  **Sair do sistema:** Encerra o programa.

**Menu do Administrador (Logado):**
-   **Atender chamado:** Inicia o fluxo de atendimento, puxando automaticamente da Heap ou da FIFO, conforme a regra de negócio.
-   **Cancelar chamado:** Permite fechar um chamado do sistema.
-   **Atualizar chamado:** Permite ao administrador modificar qualquer chamado.
-   ... (e outras funções de gerenciamento).

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="licenca"></a>
## 📝 Licença

Distribuído sob a Apache License. Veja o arquivo `LICENSE` para mais detalhes.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="autor"></a>
## 🎓 Autor
- **Nome:** Fernando Dorneles da Silva
- **Título:** Graduando em Engenharia de Computação
- **E-mail:** fernando.dorneles@ecomp.ufsm.br
- **GitHub:** [dornelesfernando](https://github.com/dornelesfernando)
- **LinkedIn:** [Fernando Dorneles da Silva](https://www.linkedin.com/in/fernandodorneles)
- **Currículo Lattes:** [Acessar Lattes](http://lattes.cnpq.br/0532418852427960)

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

<a id="agradecimentos"></a>
## 🤝 Agradecimentos

Este projeto não seria possível sem o apoio e os recursos listados abaixo:

### Pessoas e Instituições
- **[Universidade Federal de Santa Maria (UFSM)](https://www.ufsm.br/):** Pela oportunidade de cursar a graduação e pelo ambiente de aprendizado.
- **Disciplina de Estrutura de Dados e Programação:** Pelos desafios propostos e pelo conhecimento adquirido.
- **Professor Jonas Bulegon Gassen:** Pela orientação, paciência e por compartilhar seu conhecimento.

### Ferramentas e Comunidades
- **[Visual Studio Code](https://code.visualstudio.com/):** Pelo ambiente de desenvolvimento produtivo e extensível.
- **[Stack Overflow](https://stackoverflow.com/):** Pela sabedoria coletiva que resolveu inúmeros desafios ao longo do caminho.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>
