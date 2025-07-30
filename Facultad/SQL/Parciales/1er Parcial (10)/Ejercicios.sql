/**************************************************************************************************************/
/**************************************************************************************************************/

/* 01 -  ¿Cuál es el Modelo de auto más vendido? Indicar Marca y Modelo.*/

SELECT
    auto.Auto_ID,
    modelo.Modelo_DESC,
    marca.Marca_DESC,
    COUNT(venta.Auto_ID) AS cant_ventas
FROM
    auto
INNER JOIN
    modelo ON auto.Modelo_ID = modelo.Modelo_ID
INNER JOIN
    marca ON modelo.Marca_ID = marca.Marca_ID
INNER JOIN
    venta ON auto.Auto_ID = venta.Auto_ID
GROUP BY 
    auto.Auto_ID
ORDER BY
    cant_ventas DESC LIMIT 1


/**************************************************************************************************************/
/**************************************************************************************************************/

/*  02 - ¿Quién es el vendedor que más autos vendió?    */

SELECT
    (empleado.Nombre || " " || empleado.apellido) AS Empleado,
    COUNT(venta.Empleado_ID) AS cant_ventas
FROM
    empleado
INNER JOIN
    venta ON empleado.Empleado_ID = venta.Empleado_ID
GROUP BY 
    venta.Empleado_ID
ORDER BY
    cant_ventas DESC LIMIT 1
    

/**************************************************************************************************************/
/**************************************************************************************************************/

/*  03- Indicar la ganancia (Venta - Costo) del auto menos vendido.   */

SELECT
    (venta.precio_USD - auto.Costo_USD) AS Ganancia
FROM
    auto
INNER JOIN
    venta ON auto.Auto_ID = venta.Auto_ID
ORDER BY
    auto.Auto_ID LIMIT 1


/**************************************************************************************************************/
/**************************************************************************************************************/

/*  04 - Indicar cuantos autos compraron los clientes de acuerdo a rangos de edad.(Joven, Adulto, Mayor)   */

SELECT
    (CASE WHEN EDAD <= 25 THEN "Joven" WHEN EDAD <= 50 THEN "Adulto" WHEN EDAD > 50 THEN "Mayor" END) AS rango_edad,
    COUNT(VENTA.Cliente_ID) AS Cant_compras
FROM
    Cliente
INNER JOIN
    VENTA ON CLIENTE.Cliente_ID = VENTA.Cliente_ID
GROUP BY
    rango_edad

/**************************************************************************************************************/
/**************************************************************************************************************/

/*  05 - De los autos vendidos en Marzo 2024, ¿Cuántos entraron a reparar? 
         Indicar la cantidad vendida en Marzo y a su vez los autos que 
         ingresaron a reparar*/

SELECT
    venta.Auto_ID,
    COUNT(DISTINCT VENTA.Venta_ID) AS Cant_vendida_marzo,
    MANTENIMIENTO.Auto_ID AS reparaciones
FROM
    VENTA
LEFT JOIN
    MANTENIMIENTO ON VENTA.Auto_ID = MANTENIMIENTO.Auto_ID
WHERE
    VENTA.Fecha BETWEEN "2024-03-01" AND "2024-03-31"
GROUP BY 
    venta.venta_ID

/**************************************************************************************************************/
/**************************************************************************************************************/