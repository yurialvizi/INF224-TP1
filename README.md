# INF224-TP1

### Step 4:

1. Como é chamado esse tipo de método e como devem ser declarados?
   Esse tipo de método é chamado de abstrato e devem ser declarados com a palavra chave virtual com '=0' ao final.
2. Caso você tenha feito o acima solicitado, não será mais possível instanciar objetos da classe
   base. Por que ?

Porque Media não tem implementação para o método play declarado no header

### Step 5:

Qual é a propriedade característica da orientação a objetos que permite que isso seja
feito?

Polimorfismo

O que é especificamente necessário fazer no caso de C++ ?

É necessário declarar ao fim que a classe é do certo tipo como, por exemplo:  class ClassChild: public ClassParent

Qual é o tipo dos elementos do array : o array deve conter objetos ou ponteiros para
esses objetos? Para que ? Compare com Java.

O array contém ponteiros para esses objetos.
