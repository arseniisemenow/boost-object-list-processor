DROP TABLE IF EXISTS objects;
CREATE TABLE IF NOT EXISTS objects
(
    id
    SERIAL
    PRIMARY
    KEY,
    NAME
    VARCHAR
(
    255
) NOT NULL,
    x DOUBLE PRECISION NOT NULL,
    y DOUBLE PRECISION NOT NULL,
    "type" VARCHAR
(
    100
) NOT NULL,
    creation_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
    );


SELECT id, name, x, y, type, creation_time FROM objects