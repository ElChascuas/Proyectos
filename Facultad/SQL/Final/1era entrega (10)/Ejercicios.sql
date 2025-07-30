--Ejercicios tabla simple:

/*1)	Riot piensa hacer un rework para algunos de los objetos que superen los 3000 de oro en coste, 
muestra los objetos que empiecen con la letra “A” y cumplan con la anterior condición, 
en orden alfabético.*/

SELECT
*
FROM
Item
WHERE
precio > 3000 AND SUBSTRING(nombre_item,1,1) = "A"
ORDER BY
nombre_item

/*2)	Riot está muy orgulloso del desempeño por de los jugadores del famoso y dominante 
equipo competitivo “T1”, ¿Podrías mostrar los jugadores cuyos nombres empiecen con “T1” 
ordenados de mayor a menor según su nivel?*/

SELECT
    *
FROM
    Jugador
WHERE
    SUBSTRING(nombre_jugador,1,1) = "T"
ORDER BY
    nivel_jugador DESC

/*3)	Riot necesita la información de un campeón, pero no recuerda su nombre, 
solo sabe que su nombre comienza con “O” además de ser un Tanque de la línea TOP, 
muestra el campeón que cumpla con esas características.*/

SELECT
    *
FROM
    Campeon
WHERE
    id_linea = 'TOP' AND rol = 'Tanque' AND SUBSTRING(nombre_campeon,1,1) = "O"

/*4)	Los Asesinos suelen ser campeones de juego temprano, estos suelen buscar asesinatos 
rápidos que les den oro para acceder a su primer objeto y obtener ventaja temprana, 
Riot necesita saber cuales son los objetos de la categoría asesinos y que valgan menos de 2600 de oro.*/

SELECT
    *
FROM
    Item
WHERE
    precio < 2600 AND categoria = 'Asesinos'

/*5)	Podrías mostrar cuales jugadores son veteranos, avanzados, iniciados, y principiantes 
dependiendo de su nivel y ordenarlos según nivel y nombre.*/

SELECT
    *,
    CASE 
        WHEN nivel_jugador >= 750 THEN 'Veterano'
        WHEN nivel_jugador BETWEEN 749 AND 500 THEN 'Avanzado'
        WHEN nivel_jugador BETWEEN 499 AND 250 THEN 'Iniciado'
        ELSE 'Principiante'
    END AS Rango_Experiencia
FROM
    Jugador
ORDER BY
    nivel_jugador, nombre_jugador

/*6)	Riot quiere agregar nuevos campeones a roles y líneas que estén un poco olvidadas, 
cuenta cuantos campeones hay por cada línea y rol, además ordénalos según el numero de campeones.*/

SELECT
    Id_linea,
    Rol,
    COUNT(*) AS Cant_campeones
FROM
    Campeon
GROUP BY
    Id_linea, Rol
ORDER BY
    Cant_campeones DESC

/*7)	Hay categorías muy caras y otras muy baratas, los ítems de mago suelen ser muy caros 
y los de soporte muy baratos, Riot piensa balancear los costos generales de algunas categorías, 
muestra la suma total de precios entre las categorías de objetos.*/

SELECT
    categoria,
    SUM(precio) AS total_oro
FROM
    Item
GROUP BY
    categoria
ORDER BY 
    total_oro DESC

--8)	¿Podrías contar cuantas runas hay en cada rama? Riot planea agregar nuevas runas y quitar otras

SELECT
    rama,
    COUNT(*) AS cant_runas
FROM
    Runa
GROUP BY
    rama

/*9)	¿Podrías contar cuantos objetos hay en cada categoría y ordénalos de forma descendente? 
Hay categorías con demasiados objetos y otras con muy pocos*/

SELECT
    categoria,
    COUNT(*) AS cant_items
FROM
    Item
GROUP BY
    categoria
ORDER BY
    cant_items DESC

/*10)	Riot necesita todos los campeones cuyo nombre comience con “Z” y ordenados 
alfabéticamente según su linea.*/

SELECT
    *
FROM
    Campeon
WHERE
    SUBSTRING(nombre_campeon,1,1) = "Z"
ORDER BY
    Id_linea










--Ejercicios Multitabla:

--1)	Muestra los jugadores que ganaron usando runas de la rama Valor. Usa subconsultas.

SELECT
    Jugador.*
FROM
    Jugador
INNER JOIN
    Partida ON Jugador.id_jugador = Partida.id_jugador
WHERE
    resultado = 'Victoria' AND id_build IN (SELECT
                                                id_build
                                            FROM
                                                Build
                                            WHERE
                                                id_runa_clave BETWEEN 37 AND 39)
GROUP BY 
    Jugador.nombre_jugador

/*2)	¿Cuáles fueron los 5 objetos más elegidos como primer objeto de las partidas perdedoras? 
Puede que esos objetos necesiten una mejora a sus estadísticas.*/

SELECT
    item.nombre_item,
    COUNT(id_primer_itemcore) as Cant_selecciones
FROM
    build
INNER JOIN
    item ON build.id_primer_itemcore = item.id_item
INNER JOIN
    partida ON build.id_build = partida.id_build
WHERE
    partida.resultado = 'Derrota'
GROUP BY
    Item.nombre_item
ORDER BY
    Cant_selecciones DESC LIMIT 5

/*3)	Mostrar las victorias de las Runas Clave según la cantidad de victorias a manos de jugadores 
con nivel principiante y ordenarlas según victorias. Para poder nerfearlas.*/

SELECT
    Runa.nombre_runa,
    COUNT(Build.id_runa_clave) AS Cant_victorias
FROM
    Build
INNER JOIN
    Runa ON Build.id_runa_clave = Runa.id_runa
INNER JOIN
    Partida ON build.id_build = partida.id_build
INNER JOIN
    Jugador ON Partida.id_jugador = Jugador.id_jugador
WHERE
    Partida.resultado = 'Victoria' AND Jugador.nivel_jugador < 250
GROUP BY
    Runa.nombre_runa
ORDER BY
    Cant_victorias DESC

--4)	Muestra los jugadores que mas victorias consiguieron usando la runa clave “Aery”.

SELECT
    Jugador.nombre_jugador,
    COUNT(*) AS Cant_victorias
FROM
    Partida
INNER JOIN
    Jugador ON Partida.id_jugador = Jugador.id_jugador
WHERE
    Partida.resultado = 'Victoria' AND (Partida.id_build = 11 OR Partida.id_build = 21)
GROUP BY
    Jugador.nombre_jugador

/*5)	Mostrar si alguien jugo una Build que tenga Lluvia de espadas como runa clave, Akshan 
como Campeon elegido y Agrietador como primer objeto, ademas mostrar el resultado.*/

SELECT 
    Jugador.*,
    Partida.Resultado
FROM
    Partida
INNER JOIN
    Jugador ON Partida.id_jugador = Jugador.id_jugador
INNER JOIN
    Build ON Partida.id_build = Build.id_build
INNER JOIN
    Campeon ON Partida.id_campeon = Campeon.id_campeon
WHERE
    Build.id_primer_itemcore = 2 AND Build.id_runa_clave = 15 AND Partida.id_campeon = 4

/*6)	Muestra los campeónes mas baneados por jugadores que hayan usado la runa clave Conquistador
 y hayan perdido.*/

SELECT
    nombre_campeon,
    COUNT(*) AS Cant_bloqueos
FROM
    Partida
INNER JOIN
    Campeon ON Partida.id_banned_champ = Campeon.id_campeon
WHERE
    Partida.resultado = 'Derrota' AND (Partida.id_build = 1 OR Partida.id_build = 2 OR Partida.id_build = 5 OR Partida.id_build = 15)
GROUP BY
    Campeon.nombre_campeon
ORDER BY
    Cant_bloqueos DESC, nombre_campeon

/*7)	Mostrar los campeones menos jugados según su línea y rol. A lo mejor necesiten un rework 
para hacerlos mas atractivos para los jugadores.*/

SELECT 
    Id_linea, 
    Rol,
    nombre_campeon,
    COUNT(*) AS Cant_Elecciones
FROM
    Partida
INNER JOIN
    Campeon ON Partida.id_campeon = Campeon.id_campeon
GROUP BY
    nombre_campeon
ORDER BY
    id_linea, Cant_Elecciones

/*8)	Mostrar campeones que no se hayan jugado en ninguna partida. Riot planea buffearlos en el 
siguiente cambio de balance.*/

SELECT 
    Id_linea,
    Rol,
    Nombre_Campeon
FROM
    Campeon
LEFT JOIN
    Partida ON Partida.id_banned_champ = Campeon.id_campeon
WHERE
    id_entrada IS NULL
GROUP BY
    Id_linea, Rol, Nombre_campeon

/*9)	Muestra las partidas donde al menos un jugador haya usado la runa clave Cosecha Oscura 
y usado Al filo de la cordura como primero objeto, además muestra los datos del jugador que las 
uso y si ganaron o perdieron.*/

SELECT
    Id_Partida,
    nombre_jugador,
    nivel_jugador,
    resultado
FROM
    Build
INNER JOIN
    item ON Build.id_primer_itemcore = item.id_item
INNER JOIN
    Partida ON build.id_build = partida.id_build
INNER JOIN
    Jugador ON Partida.id_jugador = Jugador.id_jugador
WHERE
    Build.id_primer_itemcore = 4 AND Build.id_runa_clave = 14
GROUP BY
    partida.id_partida
ORDER BY
    nivel_jugador DESC

/*10)	Muestra jugadores que hayan perdido jugando tanques y tenga un nivel menor a 500.*/

SELECT
    Jugador.*
FROM
    Build
INNER JOIN
    Runa ON Build.id_runa_clave = Runa.id_runa
INNER JOIN
    Partida ON build.id_build = partida.id_build
INNER JOIN
    Jugador ON Partida.id_jugador = Jugador.id_jugador
INNER JOIN
    Campeon ON Partida.id_campeon = Campeon.id_campeon
WHERE
    Partida.resultado = 'Derrota' AND Campeon.rol = 'Tanque' AND Jugador.nivel_jugador < 500
GROUP BY
    Jugador.nombre_jugador
