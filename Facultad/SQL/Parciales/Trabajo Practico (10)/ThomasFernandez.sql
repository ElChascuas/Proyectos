--THOMAS FERNANDEZ

--Ejercicio 1
CREATE PROCEDURE SP_InsertarCliente
	@Id INT,
    @Nombre NVARCHAR(100),
    @Apellido NVARCHAR(100),
    @Direccion NVARCHAR(200),
    @Telefono NVARCHAR(15),
    @Email NVARCHAR(100),
    @Edad INT
AS
BEGIN
    INSERT INTO Concesionaria.dbo.Cliente (Cliente_ID, Nombre, Apellido, Direccion, Telefono, Email, Edad)
    VALUES (@Id, @Nombre, @Apellido, @Direccion, @Telefono, @Email, @Edad);
END

EXEC InsertarCliente
	@Id = 590,
    @Nombre = 'Juan', 
    @Apellido = 'Juan', 
    @Direccion = 'Calle 123', 
    @Telefono = '4444444', 
    @Email = 'juan.juan@gmail.com', 
    @Edad = 30;
GO


--Ejercicio 2
CREATE PROCEDURE SP_CambiarTelefono
	@Id INT,
	@Tel INT
AS
BEGIN
	UPDATE Cliente
	SET Telefono = @Tel
	WHERE Cliente_ID = @Id
END;

EXEC SP_CambiarTelefono @Id = 201, @Tel = 33333
GO


--Ejercicio 3
ALTER VIEW VW_ModeloFerrari AS
SELECT
	Modelo_ID
FROM
	Modelo
WHERE
	Marca_ID = 20;
GO

SELECT
	*
FROM
	Venta
WHERE
	Auto_ID in (SELECT
					Auto_ID
				FROM
					Auto
				WHERE
					Modelo_ID in (Select * FROM VW_ModeloFerrari));
GO


--Ejercicio 4
CREATE TRIGGER TRG_ClienteOnUpdate
ON Cliente
AFTER UPDATE
AS
BEGIN
	PRINT 'TABLA CLIENTE ACTUALIZADA'
END;

EXEC SP_CambiarTelefono @Id = 201, @Tel = 111111
GO


--Ejercicio 5
CREATE TRIGGER TRG_PrevenirEliminar
ON Cliente
INSTEAD OF DELETE
AS
BEGIN
    PRINT 'ELIMINACION NO PERMITIDA';
END;

DELETE FROM Cliente WHERE Cliente_ID = 1;
GO

--Ejercicio 6
CREATE FUNCTION TotalVentasEmpleado (
    @EmpleadoID INT,
    @FechaInicio DATETIME,
    @FechaFin DATETIME
)
RETURNS DECIMAL(10, 2)
AS
BEGIN
    RETURN (
        SELECT ISNULL(SUM(Precio_USD), 0)
        FROM Venta
        WHERE Empleado_ID = @EmpleadoID
          AND Fecha BETWEEN @FechaInicio AND @FechaFin
    );
END;
GO

PRINT dbo.TotalVentasEmpleado(2, '2024-03-15', '2024-03-24');
GO

--Ejercicio 7
CREATE PROCEDURE RegistrarVentaAuto
	@VentaID INT,
    @AutoID INT,
    @ClienteID INT,
    @EmpleadoID INT,
    @Precio_USD DECIMAL(10, 2),
	@NombreCliente VARCHAR(50) = NULL, 
	@ApellidoCliente VARCHAR(50) = NULL, 
	@DireccionCliente VARCHAR(100) = NULL, 
	@TelefonoCliente VARCHAR(15) = NULL, 
	@EmailCliente VARCHAR(50) = NULL, 
	@EdadCliente INT = NULL,
	@NombreEmpleado VARCHAR(50) = NULL, 
	@ApellidoEmpleado VARCHAR(50) = NULL, 
	@SalarioEmpleado DECIMAL(10, 2) = NULL, 
	@AntiguedadEmpleado INT = NULL

AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

			IF NOT EXISTS (SELECT 1 FROM Auto WHERE Auto_ID = @AutoID)
			BEGIN
				RAISERROR('El Auto no existe.', 16, 1);
				RETURN;
			END

			IF EXISTS (SELECT 1 FROM Venta WHERE Venta_ID = @VentaID)
			BEGIN
				RAISERROR('La Venta ya existe.', 16, 1);
				RETURN;
			END
			
			DECLARE @Puesto NVARCHAR(50);
			SELECT @Puesto = Puesto FROM Empleado WHERE Empleado_ID = @EmpleadoID;
			IF @Puesto IS NOT NULL AND @Puesto != 'Vendedor'
			BEGIN
				RAISERROR('El Empleado existe y no es Vendedor.', 16, 1);
				RETURN;
			END

			IF NOT EXISTS (SELECT 1 FROM Cliente WHERE Cliente_ID = @ClienteID)
			BEGIN
				INSERT INTO Cliente (Cliente_ID, Nombre, Apellido, Direccion, Telefono, Email, Edad) 
				VALUES (@ClienteID, @NombreCliente, @ApellidoCliente, @DireccionCliente, @TelefonoCliente, @EmailCliente, @EdadCliente); 
			END

			IF NOT EXISTS (SELECT 1 FROM Empleado WHERE Empleado_ID = @EmpleadoID)
			BEGIN
				INSERT INTO Empleado (Empleado_ID, Nombre, Apellido, Puesto, Salario_USD, Antiguedad) 
				VALUES (@EmpleadoID, @NombreEmpleado, @ApellidoEmpleado, 'Vendedor', @SalarioEmpleado, @AntiguedadEmpleado);
			END

			INSERT INTO Venta (Venta_ID, Auto_ID, Cliente_ID, Empleado_ID, Fecha, Precio_USD)
			VALUES (@VentaID, @AutoID, @ClienteID, @EmpleadoID, GETDATE(), @Precio_USD);

        COMMIT TRANSACTION;
    END TRY
	BEGIN CATCH
		IF @@TRANCOUNT > 0
		BEGIN
			ROLLBACK TRANSACTION;
		END

		DECLARE @ErrorMessage NVARCHAR(4000);
		DECLARE @ErrorSeverity INT;
		DECLARE @ErrorState INT;

		SELECT 
			@ErrorMessage = ERROR_MESSAGE(),
			@ErrorSeverity = ERROR_SEVERITY(),
			@ErrorState = ERROR_STATE();

		RAISERROR (@ErrorMessage, @ErrorSeverity, @ErrorState);
	END CATCH
END;
GO

EXEC RegistrarVentaAuto 
    @VentaID = 1000, 
    @AutoID = 1, 
    @ClienteID = 1000, 
    @EmpleadoID = 1000, 
    @Precio_USD = 25000.00, --aca invente, me daba demasiada paja calcular 
	--cuanto era el precio segun costo + mantenimiento + comision, si era necesario pido disculpas
    @NombreCliente = 'Juan', 
    @ApellidoCliente = 'Jose', 
    @DireccionCliente = 'Calle 1234', 
    @TelefonoCliente = '1234', 
    @EmailCliente = 'juan@hotmail.com', 
    @EdadCliente = 30,
    @NombreEmpleado = 'Jose', 
    @ApellidoEmpleado = 'Juan', 
    @SalarioEmpleado = 3000.00, 
    @AntiguedadEmpleado = 5;
GO

EXEC RegistrarVentaAuto 
    @VentaID = 1001, 
    @AutoID = 2, 
    @ClienteID = 1000, 
    @EmpleadoID = 1000, 
    @Precio_USD = 25000.00;
GO


--Ejercicio 8
CREATE PROCEDURE RegistrarMantenimientoAuto
	@VentaID INT,
    @AutoID INT,
    @ClienteID INT = NULL,
    @EmpleadoVenta INT = NULL,
    @Precio_USD DECIMAL(10, 2) = NULL,
	@MantenimientoID INT,
	@EmpleadoMantenimiento INT,
	@MantenimientoDESC TEXT,
	@Costo DECIMAL(10, 2)

AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

			IF NOT EXISTS (SELECT 1 FROM Auto WHERE Auto_ID = @AutoID)
			BEGIN
				RAISERROR('El Auto no existe.', 16, 1);
				RETURN;
			END

			IF NOT EXISTS (SELECT 1 FROM Empleado WHERE Empleado_ID = @EmpleadoVenta AND Puesto = 'Vendedor') AND @EmpleadoVenta IS NOT NULL
			BEGIN
				RAISERROR('El Empleado de ventas no existe y/o no tiene el puesto de Vendedor.', 16, 1);
				RETURN;
			END

			IF NOT EXISTS (SELECT 1 FROM Empleado WHERE Empleado_ID = @EmpleadoMantenimiento AND Puesto = 'Mecanico')
			BEGIN
				RAISERROR('El Empleado de mantenimiento no existe y/o no tiene el puesto de Mecanico.', 16, 1);
				RETURN;
			END

			IF NOT EXISTS (SELECT 1 FROM Cliente WHERE Cliente_ID = @ClienteID) AND @ClienteID IS NOT NULL
			BEGIN
				RAISERROR('El cliente no existe.', 16, 1);
				RETURN; 
			END

			IF EXISTS (SELECT 1 FROM Mantenimiento WHERE Mantenimiento_ID = @MantenimientoID)
			BEGIN
				RAISERROR('El mantenimiento_id ya fue registrado.', 16, 1);
				RETURN; 
			END

			DECLARE @AutoVendido INT;
            SELECT @AutoVendido = Auto_ID FROM Venta WHERE Venta_ID = @VentaID;
			IF EXISTS (SELECT 1 FROM Venta WHERE Venta_ID = @VentaID) AND @AutoVendido != @AutoID
			BEGIN
				RAISERROR('El Auto_ID en la venta no coincide con el Auto_ID proporcionado para mantenimiento.', 16, 1);
                RETURN;
			END

			IF NOT EXISTS (SELECT 1 FROM Venta WHERE Venta_ID = @VentaID) AND 
			@ClienteID IS NOT NULL AND @EmpleadoVenta IS NOT NULL AND @Precio_USD IS NOT NULL
			BEGIN
				RAISERROR('La venta no existe y no se dieron valores validos para crear una.', 16, 1);
                RETURN;
			END

			IF EXISTS (SELECT 1 FROM Venta WHERE Venta_ID = @VentaID) AND @AutoVendido = @AutoID
			BEGIN
				UPDATE Venta 
				SET Precio_USD = (Precio_USD + @Costo)
				WHERE Venta_ID = @VentaID;
			END

			IF NOT EXISTS (SELECT 1 FROM Venta WHERE Venta_ID = @VentaID)
			BEGIN
				INSERT INTO Venta (Venta_ID, Auto_ID, Cliente_ID, Empleado_ID, Fecha, Precio_USD)
				VALUES (@VentaID, @AutoID, @ClienteID, @EmpleadoVenta, GETDATE(), (@Precio_USD + @Costo));
			END

			IF NOT EXISTS (SELECT 1 FROM Mantenimiento WHERE Mantenimiento_ID = @MantenimientoID)
			BEGIN
				INSERT INTO Mantenimiento(Mantenimiento_ID, Auto_ID, Empleado_ID, Mantenimiento_DESC, Fecha, Costo)
				VALUES (@MantenimientoID, @AutoID, @EmpleadoMantenimiento, @MantenimientoDESC, GETDATE(), @Costo);
			END

        COMMIT TRANSACTION;
    END TRY
	BEGIN CATCH
		IF @@TRANCOUNT > 0
		BEGIN
			ROLLBACK TRANSACTION;
		END

		DECLARE @ErrorMessage NVARCHAR(4000);
		DECLARE @ErrorSeverity INT;
		DECLARE @ErrorState INT;

		SELECT 
			@ErrorMessage = ERROR_MESSAGE(),
			@ErrorSeverity = ERROR_SEVERITY(),
			@ErrorState = ERROR_STATE();

		RAISERROR (@ErrorMessage, @ErrorSeverity, @ErrorState);
	END CATCH
END;
GO


EXEC RegistrarMantenimientoAuto
    @VentaID = 2000, 
    @AutoID = 1, 
    @ClienteID = 1000, 
    @EmpleadoVenta = 1000, 
    @Precio_USD = 25000.00, 
	@MantenimientoID = 2000,
	@EmpleadoMantenimiento = 3,
	@MantenimientoDESC = 'Cambio de aceite',
	@Costo = 300.00
GO

EXEC RegistrarMantenimientoAuto
    @VentaID = 1001, 
    @AutoID = 2, 
	@MantenimientoID = 2001,
	@EmpleadoMantenimiento = 3,
	@MantenimientoDESC = 'Cambio de aceite',
	@Costo = 300.00
GO