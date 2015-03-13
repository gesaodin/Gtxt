
SELECT count(contrato_id), codigo_n
FROM `t_clientes_creditos`
GROUP BY codigo_n;



INSERT INTO `electron`.`t_ubicacion` (`oid` ,`nombre` ,`descripcion`) VALUES (NULL , 'CJS', 'Caja Seca (Principal)');
UPDATE t_clientes_creditos SET codigo_n='Zulia (Principal)' WHERE codigo_n='ZULIA';
UPDATE t_clientes_creditos SET codigo_n='Merida (Principal)' WHERE codigo_n='MERIDA';
UPDATE t_clientes_creditos SET codigo_n='Merida (Principal)' WHERE codigo_n='';
UPDATE t_clientes_creditos SET codigo_n='Sancristobal (Principal)' WHERE codigo_n='SAN CRISTOBAL';
UPDATE t_clientes_creditos SET codigo_n='Barina (Principal)' WHERE codigo_n='BARINAS';
UPDATE t_clientes_creditos SET codigo_n='El Vigia (Principal)' WHERE codigo_n='EL VIGIA';
UPDATE t_clientes_creditos SET codigo_n='Santa Barbara Del Zulia (Principal)' WHERE codigo_n='SANTA BARBARA';
UPDATE t_clientes_creditos SET codigo_n='Caja Seca (Principal)' WHERE codigo_n='CAJA SECA';

/*
 * 
 */
UPDATE t_clientes_creditos SET cobrado_en='----------' WHERE cobrado_en='';

UPDATE t_clientes_creditos SET nomina_procedencia='----------' WHERE nomina_procedencia='';
UPDATE t_clientes_creditos SET nomina_procedencia='ALCALDIA DEL MUNICIPIO CAMPO ELIAS (EJIDO)' WHERE nomina_procedencia='ALCALDIA DEL MUNICIPIO CAMPO ELIAS';
UPDATE t_clientes_creditos SET nomina_procedencia='CANTV' WHERE nomina_procedencia='CANTV - JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='COORPORACION VENEZOLANA DE GUAYANA (CVG)' WHERE nomina_procedencia='COORPORACION VENEZOLANA DE GUAYANA (CVG) ACTIVOS';
UPDATE t_clientes_creditos SET nomina_procedencia='COORPORACION VENEZOLANA DE GUAYANA (CVG)' WHERE nomina_procedencia='COORPORACION VENEZOLANA DE GUAYANA (CVG) JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE BARINAS' WHERE nomina_procedencia='GOBERNACION BARINAS';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE BARINAS' WHERE nomina_procedencia='GOBERNACION BARINAS (DOCENTES)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE BARINAS' WHERE nomina_procedencia='GOBERNACION BARINAS (POLICIA)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE BARINAS' WHERE nomina_procedencia='GOBERNACION BARINAS (SALUD)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE CARABOBO' WHERE nomina_procedencia='GOBERNACION DE CARABOBO (ACTIVOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE CARABOBO' WHERE nomina_procedencia='GOBERNACION DE CARABOBO (SECRETARIA DE EDUCACION)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE CARABOBO' WHERE nomina_procedencia='GOBERNACION DE CARABOBO JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE FALCON' WHERE nomina_procedencia='GOBERNACION DE FALCON -DOCENTES';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE LARA' WHERE nomina_procedencia='GOBERNACION DE LARA ( DOCENTES)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE LARA' WHERE nomina_procedencia='GOBERNACION DE LARA (JUBILADOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE LARA' WHERE nomina_procedencia='GOBERNACION DE LARA (SALUD)';
UPDATE t_clientes_creditos SET nomina_procedencia='GOBERNACION DE LARA' WHERE nomina_procedencia='GOBERNACION DE LARA EMPLEADOS/OBREROS';
UPDATE t_clientes_creditos SET nomina_procedencia='ALCADIA DE VALENCIA' WHERE nomina_procedencia='ALCADIA DE VALENCIA (JUBILADOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='ALCADIA DE VALENCIA' WHERE nomina_procedencia='ALCALDIA DE VALENCIA (ACTIVOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='INAM' WHERE nomina_procedencia='INAM - JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='IPASME' WHERE nomina_procedencia='IPASME - JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='IPOSTEL' WHERE nomina_procedencia='IPOSTEL - JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='IVSS' WHERE nomina_procedencia='IVSS - JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='IVSS' WHERE nomina_procedencia='IVSS JUBILADO';
UPDATE t_clientes_creditos SET nomina_procedencia='SIDERURGICA DEL ORINOCO' WHERE nomina_procedencia='SIDERURGICA DEL ORINOCO (ACTIVOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='SIDERURGICA DEL ORINOCO' WHERE nomina_procedencia='SIDERURJICA DEL ORINOCO (ACTIVOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='SAREM' WHERE nomina_procedencia='SAREN';
UPDATE t_clientes_creditos SET nomina_procedencia='MINISTERIO DEL PODER POPULAR PARA LA EDUCACION' WHERE nomina_procedencia='MINISTERIO DEL PODER POPULAR PARA LA EDUCACION - JUBILADO';
UPDATE t_clientes_creditos SET nomina_procedencia='MINISTERIO DE SALUD' WHERE nomina_procedencia='MINISTERIO DE SALUD (JUBILADOS)';
UPDATE t_clientes_creditos SET nomina_procedencia='MINISTERIO DE TRANSPORTE Y COMUNICACION' WHERE nomina_procedencia='MINISTERIO DE TRANSPORTE Y COMUNICACION-JUBILADOS';
UPDATE t_clientes_creditos SET nomina_procedencia='MINISTERIO DE TRANSPORTE Y COMUNICACION' WHERE nomina_procedencia='MINISTERIO DE TRANSPORTE Y COMUNICACIONES';
UPDATE t_clientes_creditos SET nomina_procedencia='MINISTERIO DE LA SALUD' WHERE nomina_procedencia='MINISTERIO DE SALUD';


--
-- Actualizar Cuentas Crear Responsables Creadores del Contrato
--

UPDATE t_clientes_creditos SET codigo_n_a='Marly' WHERE codigo_n_a='Marlin';
INSERT INTO `electron`.`t_usuario` (`oid`, `documento_id`, `descripcion`, `seudonimo`, `clave`, `correo`, `fecha`, `estatus`, `conectado`) 
VALUES ('71', '71', 'ALEJANDRA', 'ALEJANDRA', '', '', '', '0', '0'),
('72', '72', 'GENESIS', 'GENESIS', '', '', '', '0', '0'),
('73', '73', 'kary', 'kary', '', '', '', '0', '0'),
('74', '74', 'AuxAlejandra', 'AuxAlejandra', '', '', '', '0', '0'),
('75', '75', 'SANCRISTOBAL', 'SANCRISTOBAL', '', '', '', '0', '0'),
('76', '76', 'LASTEJAS', 'LASTEJAS', '', '', '', '0', '0'),
('77', '77', 'SANTABARBARA', 'SANTABARBARA', '', '', '', '0', '0'),
('78', '78', 'barinas465', 'barinas465', '', '', '', '0', '0'),
('79', '79', 'Auxiliar', 'Auxiliar', '', '', '', '0', '0'),
('80', '80', 'ELVIGIA', 'ELVIGIA', '', '', '', '0', '0'),
('81', '81', 'Zulia-Jhoander', 'Zulia-Jhoander', '', '', '', '0', '0'),
('82', '82', 'CAJASECA', 'CAJASECA', '', '', '', '0', '0'),
('83', '83', 'admin', 'admin', '', '', '', '0', '0'),
('84', '84', 'General', 'General', '', '', '', '0', '0');

UPDATE t_clientes_creditos SET codigo_n_a='General' WHERE codigo_n_a='';
