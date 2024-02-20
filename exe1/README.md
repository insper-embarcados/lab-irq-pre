# Exercício 1

Até o final do semestre iremos trabalhar com diversos periféricos e diferentes tipos de interrupção, por enquanto vamos mexer com interrupções de GPIO. O GPIO pode gerar interrupção para diferentes situações:

1. Borda de Descida (exe: botão apertado)
1. Borda de Subida (exe: botão solto)
1. Nível 

## Código

Para usarmos interrupção no GPIO, temos que primeiro configurar o pino como entrada (ativando ou não pull-up) e então ativarmos o IRQ usando a função `gpio_set_irq_enabled_with_callback` que recebe como argumento:

1. O tipo de evento (subida / descida, ..): `GPIO_IRQ_EDGE_FALL`, `GPIO_IRQ_EDGE_RISE`.
1. Se a IRQ está ou não ativa 
1. A funcã́o de callback, que será chamada quando uma interrupcao for detectada pelo periférico GPIO.

Exemplo:

``` c
  gpio_set_irq_enabled_with_callback(
      BTN_0, GPIO_IRQ_EDGE_FALL, true, &gpio_callback
  );
```

A função de callback pode ser algo como:

```
void gpio_callback(uint gpio, uint32_t events) {
    gpio_put(LED_0, 1);
    sleep_ms(150);
    gpio_put(LED_0, 0);
}
```
## Tarefa

Modifique o código `main.c` para o LED piscar quando o botão for pressionado OU solto! Para isso você pode substituir:

```diff
- GPIO_IRQ_EDGE_FALL,

por:

+ GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
```

> Indicamos para vocês testarem primeiro online no wokwi e depois validam no CI.

| Diagrama         | ![](https://docs.wokwi.com/pt-BR/img/logo.svg)                    |
|------------------|-------------------------------------------------------------------|
| ![](diagram.png) | [Open in in wokwi](https://wokwi.com/projects/385949021752215553) |

### Cenário de teste

O teste verifica se o LED começa apagado e se acende depois de `250ms`
