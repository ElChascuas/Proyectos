USE master;
CREATE DATABASE Prueba_JSON;
GO

USE Prueba_JSON;
create table JsonData (
	ID INT PRIMARY KEY,
	DATOS VARCHAR(MAX)
)

CREATE TABLE #JsonDataChanges (
    EntryID INT PRIMARY KEY,
	EntryDate DATETIME,
	NewData NVARCHAR(MAX)
);
GO

CREATE TRIGGER TRG_JSON_TRACKER
ON JsonData
AFTER INSERT
AS
BEGIN

	IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN JsonData j ON i.ID = j.ID
    )
    BEGIN
        RAISERROR('ID ya existente', 16, 1);
        ROLLBACK TRANSACTION;
        RETURN;
    END

	INSERT INTO #JsonDataChanges (EntryID, EntryDate, NewData)
    SELECT ID, GETDATE(), DATOS 
    FROM inserted;

END;
GO

DECLARE @Json VARCHAR(MAX);

-- Leer el archivo JSON y almacenarlo en la variable @Json
SELECT @Json = CAST(BulkColumn AS VARCHAR(MAX)) 
FROM OPENROWSET(BULK 'C:\Users\Presentacion\Desktop\MOCK_DATA.json', SINGLE_BLOB) AS j;

-- Verificar el contenido de @Json
SELECT @Json;

-- Insertar en la tabla JsonData
INSERT INTO JsonData (ID, DATOS)
VALUES (1, @Json);

SELECT * FROM JsonData






