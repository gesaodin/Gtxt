--
-- Personas Basado en t_personas
--
INSERT INTO grupo.t_persona(`ced`, `pnmb`, `snmb`, `pape`, `sape`, `fnac`, `sexo`, `tele`, `celu`, `obse`, `zpos`, `muni`, 
`parr`, `sect`, `aven`, `urba`, `cal`, `rif`) 
SELECT `documento_id`, `primer_nombre`, `segundo_nombre`, `primer_apellido`, `segundo_apellido`, `fecha_nacimiento`,`sexo`,
`telefono`, `celular`, `observacion`, `gaceta`,`municipio`,`parroquia`,`sector`, `avenida` , `urbanizacion`, `calle`, `rif` 
FROM electron.t_personas;

--
-- Preparar Banco
--
INSERT INTO grupo.t_banco (nmbr) SELECT  electron.t_banco.nombre FROM electron.t_banco;

INSERT INTO `grupo`.`t_banco` (`oid`, `nmbr`, `desc`, `esta`) VALUES 
(NULL, 'NOMINA', '', '1'), 
(NULL, 'DOMICILIACION POR OFICINA', '', '1'), 
(NULL, 'CAMARA MERCANTIL', '', '1'),
(NULL, 'INVERCRESA', '', '1'),
(NULL, 'CREDINFO', '', '1');

--
-- Preparar Nomina
--
INSERT INTO grupo.t_nomina (nmbr) 
SELECT electron.t_clientes_creditos.nomina_procedencia 
FROM electron.t_clientes_creditos 
GROUP BY electron.t_clientes_creditos.nomina_procedencia;

--
-- Relacion de Bancos Basado en t_personas Banco 1
--
INSERT INTO _r_personabanco (oidp,oidb,cuenta,tipo)
SELECT grupo.t_persona.oid, grupo.t_banco.oid, `cuenta_1` , `tipo_cuenta_1`
FROM electron.t_personas
JOIN grupo.t_banco ON electron.t_personas.banco_1 = grupo.t_banco.nmbr
JOIN grupo.t_persona ON electron.t_personas.documento_id = grupo.t_persona.ced;

--
-- Relacion de Bancos Basado en t_personas Banco 2
--
INSERT INTO _r_personabanco (oidp,oidb,cuenta,tipo)
SELECT grupo.t_persona.oid, grupo.t_banco.oid, `cuenta_2` , `tipo_cuenta_2`
FROM electron.t_personas
JOIN grupo.t_banco ON electron.t_personas.banco_2 = grupo.t_banco.nmbr
JOIN grupo.t_persona ON electron.t_personas.documento_id = grupo.t_persona.ced
WHERE electron.t_personas.banco_2 != '----------'
AND (electron.t_personas.cuenta_2 != '----------' AND electron.t_personas.cuenta_2 != '');

UPDATE `_r_personabanco` SET `tipo`=1 WHERE tipo='AHORRO NOMINA';
UPDATE `_r_personabanco` SET `tipo`=2 WHERE tipo='AHORRO';
UPDATE `_r_personabanco` SET `tipo`=2 WHERE tipo='----------';
UPDATE `_r_personabanco` SET `tipo`=3 WHERE tipo='CORRIENTE NOMINA';
ALTER TABLE `_r_personabanco` CHANGE `tipo` `tipo` INT( 1 ) NOT NULL COMMENT '1: Nomina 2: Ahorro 3: Corriente';



INSERT INTO grupo.t_usuario (
grupo.t_usuario.oid,grupo.t_usuario.ced,grupo.t_usuario.desc,grupo.t_usuario.seud,
grupo.t_usuario.clav,grupo.t_usuario.corr,grupo.t_usuario.fech,
grupo.t_usuario.esta,grupo.t_usuario.cone
)
SELECT * FROM electron.t_usuario;


