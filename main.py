def readFile(fileName):
    with open(fileName, 'r') as f:
       for caractere in f:
          print(caractere)
 

def main():
   readFile('teste.c')

if __name__ == "__main__":
    main()

