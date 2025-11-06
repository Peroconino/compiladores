# 📚 Compiladores – UFU

Este repositório contém materiais, códigos e experimentos desenvolvidos durante a disciplina de **Compiladores** da **Universidade Federal de Uberlândia (UFU)**.  
O objetivo é manter um ambiente organizado e isolado para estudo e implementação dos módulos que compõem um compilador, como análise léxica, sintática, semântica e geração de código.

---

## ✅ Recomendações iniciais

Para trabalhar com o projeto de forma organizada e evitar conflitos de dependências entre diferentes versões de bibliotecas, **é fortemente recomendado criar um ambiente virtual Python**.

---

## 🧪 Criando e gerenciando o ambiente virtual

A seguir estão os comandos essenciais para configurar corretamente seu ambiente de desenvolvimento.

### ✅ Criar o ambiente virtual
```bash
python -m venv nome_do_ambiente
```

### ✅ Ativar o ambiente virtual
```bash
source nome_do_ambiente/bin/activate
```

### 🔹 Windows (CMD)
```bash
nome_do_ambiente\Scripts\activate
```

### 🔹 Windows (PowerShell)
```bash
nome_do_ambiente\Scripts\Activate.ps1
```

✅ Desativar o ambiente virtual
```bash
deactivate
```

### ✅ Instalar pacotes
```bash
pip install nome_do_pacote
```

### 📦 Dependências
Caso este projeto tenha um arquivo requirements.txt, você pode instalar tudo de uma vez:
```bash
pip install -r requirements.txt
```