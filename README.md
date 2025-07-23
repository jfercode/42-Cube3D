# 42-Cube3D 🕹️🧊

Cube3D es un proyecto de la escuela 42 que explora los fundamentos de la **programación gráfica en C** y el desarrollo de un motor de renderizado en 3D sencillo, inspirado en los clásicos juegos de tipo **Wolfenstein 3D**. El objetivo es crear una simulación de entorno 3D usando técnicas de **raycasting**, gestionando eventos de usuario y renderizando un mapa en perspectiva.

<div align="center">
  <img src="https://github.com/jfercode/42-Cube3D/blob/main/assets/cube3d-demo.gif" alt="Cube3D-demo" width="400"/>
  <br/>
</div>

## Descripción del Proyecto 📖 

El programa simula un entorno tridimensional en primera persona, donde el usuario puede moverse por un mapa con paredes, espacios abiertos y objetos. Utiliza **raycasting** para calcular la proyección de paredes y renderizar la escena en tiempo real, permitiendo movimiento, rotación y detección de colisiones.

Entre los retos principales están el manejo de la entrada del usuario (teclado y ratón), la gestión eficiente de la memoria, y el renderizado de los elementos gráficos usando la librería **MiniLibX**.

## Características Principales 🌟

- 🧭 Movimiento en el entorno: avanzar, retroceder, girar izquierda/derecha.
- 🖼️ Renderizado de paredes, suelo y techo en perspectiva 3D.
- 🧊 Soporte para texturas personalizadas en los muros.
- 🚪 Detección de colisiones para evitar atravesar paredes.
- 🖱️ Gestión de eventos del teclado y ratón.
- 🔄 Minimapa opcional para navegación visual.

## Reglas y Restricciones del Proyecto 📜  

- El mapa debe ser **cerrado** y sin fugas (no debe haber espacios abiertos que permitan salir del entorno).
- El jugador debe iniciar en una posición válida y orientado hacia una dirección.
- El programa debe manejar correctamente los errores de archivo y argumentos.
- No está permitido el uso de librerías gráficas externas, salvo **MiniLibX**.
- El código debe ser conforme a la **Norma de 42** y seguir buenas prácticas de organización.

## Bonus Features 🎮✨

La versión **bonus** de Cube3D añade funcionalidades avanzadas para mejorar la experiencia de usuario y la jugabilidad:

- 🖱️ **Rotación de cámara con el ratón**: Ahora puedes girar la cámara suavemente a la izquierda o derecha simplemente moviendo el ratón, lo que facilita la exploración y añade una sensación más inmersiva de control en primera persona.
- 🚪 **Interacción con puertas**: Puedes abrir puertas dentro del mapa pulsando la tecla `E`. Esto permite acceder a nuevas áreas, agregar elementos de puzzle y crear mapas más dinámicos y variados.
- 🗺️ **Minimapa interactivo**: Se visualiza un minimapa en pantalla que representa la disposición del mapa y la posición actual del jugador. El minimapa facilita la navegación y el reconocimiento espacial, mostrando en tiempo real dónde te encuentras y hacia dónde te diriges.

Estas mejoras hacen que Cube3D sea más completo y dinámico, acercándose a la experiencia de los juegos clásicos pero con controles modernos y un entorno más interactivo.

<div align="center">
  <img src="https://github.com/jfercode/42-Cube3D/blob/main/assets/cube3d-bonus-demo.gif" alt="Cube3D-demo" width="400"/>
  <br/>
</div>

## Uso del Programa 🏃  

Para compilar y ejecutar Cube3D, utiliza los siguientes comandos en tu terminal dentro del directorio del proyecto:

- **`make all`**: Compila el proyecto y genera el ejecutable `cub3D`.

- **`make bonus`**: Compila el proyecto en modo bonus y genera el ejecutable `cub3D`.

- **`make clean`**: Elimina los archivos objeto (`.o`) generados durante la compilación.
- **`make fclean`**: Ejecuta el comando `clean` y elimina el ejecutable generado.
- **`make re`**: Ejecuta los comandos `fclean` y `all`, recompilando todo el proyecto desde cero.

Una vez compilado, el proyecto se ejecuta con:

```sh
./cub3D <ruta_al_mapa.cub>
```

### Formato del Mapa 📌

El archivo de mapa (`.cub`) debe especificar:

  - **Texturas de paredes** (N, S, E, W)
  - **Colores de suelo y techo**
  - **Mapa en formato de caracteres** (1: pared, 0: espacio, N/S/E/W: posición y orientación inicial del jugador)

Ejemplo de archivo `.cub`:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1020N1
100001
111111
```

### Ejemplo de ejecución 
```sh
./cub3D maps/mi_mapa.cub
```
Esto abrirá la ventana de Cube3D y podrás moverte por el entorno 3D generado a partir del mapa.

## Casos de error ⚠️

El programa mostrará un mensaje de error si:

- ❌ El archivo de mapa no existe o tiene formato incorrecto.
- 🔢 Se especifica un número erróneo de argumentos.
- 📉 El mapa contiene valores no válidos, está abierto o hay posiciones iniciales inválidas.
- 🖼️ Las texturas o colores no están correctamente definidos.

## Configuración y Personalización 🛠️

Puedes ajustar opciones de compilación en el **Makefile** según tus necesidades, y modificar las texturas y colores del mapa para personalizar la experiencia visual.

## Autores 🤝💡📬

<div align="center">

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/jfercode">
       <img src="https://github.com/jfercode.png" width="200px" alt="Javier Fernández Correa" />
        <br />
        <sub><b>Javier Fernández Correa</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/pexpalacios">
        <img src="https://github.com/pexpalacios.png" width="200px" alt="Penélope Palacios Alvira" />
        <br />
        <sub><b>Penélope Palacios Alvira</b></sub>
      </a>
    </td>
  </tr>
</table>

</div>