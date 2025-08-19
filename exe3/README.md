# exe 3

![](func.gif)

O código fornecido configura a interrupção no pino de dois botões e, toda vez que um deles for pressionado, imprime `fall red` ou `fall green` no terminal. O código funciona, mas possui ==um erro de qualidade de código!== Não devemos usar `printf` dentro de interrupções!

Modifique o código adicionando agora duas flags e realize o `printf` na função `main`. O comportamento deve ser o mesmo, mas a forma como lidaremos com o evento é diferente!
