CREATE TABLE Peliculas (
	Id INT PRIMARY KEY,
	Nombre NVARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Salas (
	Id INT PRIMARY KEY,
	Posicion INT NOT NULL CHECK(Posicion < 5),
	Piso INT NOT NULL CHECK(Piso < 3),
	Asientos INT NOT NULL
);

CREATE TABLE Empleados (
	Id INT PRIMARY KEY,
	Nombre NVARCHAR(20) NOT NULL,
	Apellido NVARCHAR(20) NOT NULL,
	Edad INT NOT NULL CHECK(Edad BETWEEN 14 AND 60),
);

CREATE TABLE Funciones (
	Id INT PRIMARY KEY,
	Pelicula INT FOREIGN KEY REFERENCES Peliculas(Id),
	Sala INT FOREIGN KEY REFERENCES Salas(Id),
	Boletero INT FOREIGN KEY REFERENCES Empleados(Id),
	Fecha DATETIME NOT NULL
);

INSERT INTO Peliculas VALUES (1, 'El Se�or de los anillos');
INSERT INTO Peliculas VALUES (2, 'Batman');
INSERT INTO Peliculas VALUES (3, 'Harry Potter');
INSERT INTO Peliculas VALUES (4, 'Hereditary');
INSERT INTO Peliculas VALUES (5, 'Origen');
INSERT INTO Peliculas VALUES (6, 'Django Sin Cadenas');
INSERT INTO Peliculas VALUES (7, 'Bastardos sin gloria');

INSERT INTO Salas VALUES (1, 1, 1, 30);
INSERT INTO Salas VALUES (2, 2, 1, 30);
INSERT INTO Salas VALUES (3, 3, 1, 30);
INSERT INTO Salas VALUES (4, 4, 1, 30);
INSERT INTO Salas VALUES (5, 1, 2, 30);
INSERT INTO Salas VALUES (6, 2, 2, 30);
INSERT INTO Salas VALUES (7, 3, 2, 30);
INSERT INTO Salas VALUES (8, 4, 2, 30);

INSERT INTO Empleados VALUES (1, 'Fulano', 'Funlao', 15);
INSERT INTO Empleados VALUES (2, 'Javi', 'Hola', 16);
INSERT INTO Empleados VALUES (3, 'Marcelo', 'Agachado', 17);
INSERT INTO Empleados VALUES (4, 'Piter', 'Capusoto', 19);
INSERT INTO Empleados VALUES (5, 'Elva', 'Nanero',20);
INSERT INTO Empleados VALUES (6, 'Ete', 'Sech', 21);
INSERT INTO Empleados VALUES (7, 'No', 'Se', 22);
INSERT INTO Empleados VALUES (8, 'No', 'Sabe', 23);

INSERT INTO Funciones VALUES (1, 1, 1, 1, '2022-04-22 11:34:23');
INSERT INTO Funciones VALUES (2, 4, 7, 2, '2022-04-22 13:34:23');
INSERT INTO Funciones VALUES (3, 7, 5, 5, '2022-04-22 14:34:23');
INSERT INTO Funciones VALUES (4, 3, 2, 7, '2022-04-22 15:34:23');
INSERT INTO Funciones VALUES (5, 4, 4, 8, '2022-04-23 11:34:23');
INSERT INTO Funciones VALUES (6, 6, 3, 4, '2022-04-23 13:34:23');
INSERT INTO Funciones VALUES (7, 2, 6, 3, '2022-04-23 15:34:23');


SELECT 
	*
FROM
	Funciones
INNER JOIN Peliculas
	ON Funciones.Pelicula = Peliculas.Id
INNER JOIN Salas
	ON Funciones.Sala = Salas.Id
INNER JOIN Empleados
	ON Funciones.Boletero = Empleados.Id

BACKUP DATABASE Cine
TO DISK = 'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\Backup\Cine.Bak'
WITH INIT;

RESTORE DATABASE Cine
FROM DISK = 'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\Backup\Cine.Bak'
