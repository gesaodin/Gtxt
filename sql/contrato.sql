--
-- AUXILIAR
--
CREATE TABLE IF NOT EXISTS `AUX` (
  `ncon` varchar(32) NOT NULL COMMENT 'Numero de Contrato',
  `soli` date NOT NULL COMMENT 'Fecha de Solicitud',
  `icob` date NOT NULL COMMENT 'Fecha de Inicio de Cobro',
  `motv` int(11) NOT NULL COMMENT 'Motivo',
  `cond` int(11) NOT NULL COMMENT 'Codicion',
  `tipo` int(11) NOT NULL COMMENT 'Forma de Pago Domiciliado, Voucher',
  `form` int(11) NOT NULL COMMENT 'Tipo Aguinaldos, Vacaciones, Unico',
  `peri` int(11) NOT NULL COMMENT 'Periodo Mensual, Quincenal, Anual',
  `empr` int(11) NOT NULL COMMENT 'Empresas Cooperativa Grupo',
  `ncuo` int(11) NOT NULL COMMENT 'Numero de Cuotas',
  `mcuo` decimal(10,2) NOT NULL COMMENT 'Numero de Cuotas',
  `cant` decimal(10,2) NOT NULL COMMENT 'Cantidad de las Cuotas',
  `mont` decimal(10,2) NOT NULL COMMENT 'Monto de las Cuotas',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `oidn` int(11) NOT NULL COMMENT 'Referencia Nomina Clave Foranea',
  `oidf` varchar(32) NOT NULL COMMENT 'Referecia Factura Clave Foranea',
  `oidl` int(11) NOT NULL COMMENT 'Referencia Linaje Banco  Clave Foranea',
  `oidr` varchar(32) NOT NULL COMMENT 'Identificador Responsable',
  `obse` text NOT NULL COMMENT 'Numero de Cuotas'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Objeto Contratos';

--
-- Marca Consulta lleva el Tipo de Pago
-- DOMICILIACION VOUCHER
--

INSERT INTO `electron`.`AUX` (
`ncon`,`soli` ,`icob` ,`motv` ,`cond` , 
`tipo`,`form` ,`peri` ,`empr` ,`ncuo` ,
`mcuo`,`cant` ,`mont` ,`crea` ,`oidn` ,
`oidf`,`oidl` ,`oidr`,`obse`
) 
SELECT 
 electron.t_clientes_creditos.contrato_id AS ncon,
 electron.t_clientes_creditos.fecha_solicitud  AS soli,
 electron.t_clientes_creditos.fecha_inicio_cobro  AS icob,
 electron.t_clientes_creditos.motivo  AS motv,
 electron.t_clientes_creditos.condicion  AS cond,
 electron.t_clientes_creditos.marca_consulta  AS tipo,
 electron.t_clientes_creditos.forma_contrato  AS form,
 electron.t_clientes_creditos.periocidad  AS peri,
 electron.t_clientes_creditos.empresa  AS empr,
 electron.t_clientes_creditos.numero_cuotas  AS ncuo,
 electron.t_clientes_creditos.monto_cuota  AS mcuo,
 electron.t_clientes_creditos.cantidad  AS cant,
 electron.t_clientes_creditos.monto_total  AS mont,
 electron.t_clientes_creditos.fecha_verificado  AS crea, 
 grupo.t_nomina.oid  AS oidn,
 electron.t_clientes_creditos.numero_factura  AS oidf, 
 grupo.t_banco.oid  AS oidl,
 electron.t_clientes_creditos.codigo_n_a  AS oidr,
 electron.t_clientes_creditos.observaciones  AS obse
FROM electron.t_clientes_creditos
INNER JOIN grupo.t_nomina ON grupo.t_nomina.nmbr=electron.t_clientes_creditos.nomina_procedencia
INNER JOIN grupo.t_banco ON grupo.t_banco.nmbr=electron.t_clientes_creditos.cobrado_en; 

--
-- AUXILIAR 1
--
CREATE TABLE IF NOT EXISTS `AUX_1` (
  `ncon` varchar(32) NOT NULL COMMENT 'Numero de Contrato',
  `soli` date NOT NULL COMMENT 'Fecha de Solicitud',
  `icob` date NOT NULL COMMENT 'Fecha de Inicio de Cobro',
  `motv` int(11) NOT NULL COMMENT 'Motivo',
  `cond` int(11) NOT NULL COMMENT 'Codicion',
  `tipo` int(11) NOT NULL COMMENT 'Forma de Pago Domiciliado, Voucher',
  `form` int(11) NOT NULL COMMENT 'Tipo Aguinaldos, Vacaciones, Unico',
  `peri` int(11) NOT NULL COMMENT 'Periodo Mensual, Quincenal, Anual',
  `empr` int(11) NOT NULL COMMENT 'Empresas Cooperativa Grupo',
  `ncuo` int(11) NOT NULL COMMENT 'Numero de Cuotas',
  `mcuo` decimal(10,2) NOT NULL COMMENT 'Numero de Cuotas',
  `cant` decimal(10,2) NOT NULL COMMENT 'Cantidad de las Cuotas',
  `mont` decimal(10,2) NOT NULL COMMENT 'Monto de las Cuotas',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `oidn` int(11) NOT NULL COMMENT 'Referencia Nomina Clave Foranea',
  `oidf` varchar(32) NOT NULL COMMENT 'Referecia Factura Clave Foranea',
  `oidl` int(11) NOT NULL COMMENT 'Referencia Linaje Banco  Clave Foranea',
  `oidr` varchar(32) NOT NULL COMMENT 'Identificador Responsable',
  `obse` text NOT NULL COMMENT 'Numero de Cuotas'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Objeto Contratos';

INSERT INTO `electron`.`AUX_1` (
`ncon`,`soli` ,`icob` ,`motv` ,`cond` , 
`tipo`,`form` ,`peri` ,`empr` ,`ncuo` ,
`mcuo`,`cant` ,`mont` ,`crea` ,`oidn` ,
`oidf`,`oidl` ,`oidr`,`obse`
)  
SELECT 
 electron.AUX.ncon,
 electron.AUX.soli,
 electron.AUX.icob,
 electron.AUX.motv,
 electron.AUX.cond,
 electron.AUX.tipo,
 electron.AUX.form,
 electron.AUX.peri,
 electron.AUX.empr,
 electron.AUX.ncuo,
 electron.AUX.mcuo,
 electron.AUX.cant,
 electron.AUX.mont,
 electron.AUX.crea, 
 electron.AUX.oidn,
 grupo.t_factura.oid  AS oidf,
 electron.AUX.oidl,
 electron.AUX.oidr,
 electron.AUX.obse
FROM electron.AUX
INNER JOIN grupo.t_factura ON grupo.t_factura.nfac=electron.AUX.oidf; 


--
-- AUXILIAR 2
--
CREATE TABLE IF NOT EXISTS `AUX_2` (
  `ncon` varchar(32) NOT NULL COMMENT 'Numero de Contrato',
  `soli` date NOT NULL COMMENT 'Fecha de Solicitud',
  `icob` date NOT NULL COMMENT 'Fecha de Inicio de Cobro',
  `motv` int(11) NOT NULL COMMENT 'Motivo',
  `cond` int(11) NOT NULL COMMENT 'Codicion',
  `tipo` int(11) NOT NULL COMMENT 'Forma de Pago Domiciliado, Voucher',
  `form` int(11) NOT NULL COMMENT 'Tipo Aguinaldos, Vacaciones, Unico',
  `peri` int(11) NOT NULL COMMENT 'Periodo Mensual, Quincenal, Anual',
  `empr` int(11) NOT NULL COMMENT 'Empresas Cooperativa Grupo',
  `ncuo` int(11) NOT NULL COMMENT 'Numero de Cuotas',
  `mcuo` decimal(10,2) NOT NULL COMMENT 'Numero de Cuotas',
  `cant` decimal(10,2) NOT NULL COMMENT 'Cantidad de las Cuotas',
  `mont` decimal(10,2) NOT NULL COMMENT 'Monto de las Cuotas',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `oidn` int(11) NOT NULL COMMENT 'Referencia Nomina Clave Foranea',
  `oidf` varchar(32) NOT NULL COMMENT 'Referecia Factura Clave Foranea',
  `oidl` int(11) NOT NULL COMMENT 'Referencia Linaje Banco  Clave Foranea',
  `oidr` varchar(32) NOT NULL COMMENT 'Identificador Responsable',
  `obse` text NOT NULL COMMENT 'Numero de Cuotas'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Objeto Contratos';

INSERT INTO `electron`.`AUX_2` (
`ncon`,`soli` ,`icob` ,`motv` ,`cond` , 
`tipo`,`form` ,`peri` ,`empr` ,`ncuo` ,
`mcuo`,`cant` ,`mont` ,`crea` ,`oidn` ,
`oidf`,`oidl` ,`oidr`,`obse`
)  
SELECT 
 electron.AUX_1.ncon,
 electron.AUX_1.soli,
 electron.AUX_1.icob,
 electron.AUX_1.motv,
 electron.AUX_1.cond,
 electron.AUX_1.tipo,
 electron.AUX_1.form,
 electron.AUX_1.peri,
 electron.AUX_1.empr,
 electron.AUX_1.ncuo,
 electron.AUX_1.mcuo,
 electron.AUX_1.cant,
 electron.AUX_1.mont,
 electron.AUX_1.crea, 
 electron.AUX_1.oidn,
 electron.AUX_1.oidf,
 electron.AUX_1.oidl,
 grupo.t_usuario.oid AS oidr,
 electron.AUX_1.obse
FROM electron.AUX_1 
INNER JOIN grupo.t_usuario ON grupo.t_usuario.seud=electron.AUX_1.oidr;


--
-- Crear la Tabla Contratos Relacional
--

INSERT INTO `grupo`.`t_contrato` (
`ncon`,`soli` ,`icob` ,`motv` ,`cond` , 
`tipo`,`form` ,`peri` ,`empr` ,`ncuo` ,
`mcuo`,`cant` ,`mont` ,`crea` ,`oidn` ,
`oidf`,`oidl` ,`oidr`,`obse`
)  
SELECT 
 electron.AUX_2.ncon,
 electron.AUX_2.soli,
 electron.AUX_2.icob,
 electron.AUX_2.motv,
 electron.AUX_2.cond,
 electron.AUX_2.tipo,
 electron.AUX_2.form,
 electron.AUX_2.peri,
 electron.AUX_2.empr,
 electron.AUX_2.ncuo,
 electron.AUX_2.mcuo,
 electron.AUX_2.cant,
 electron.AUX_2.mont,
 electron.AUX_2.crea, 
 electron.AUX_2.oidn,
 electron.AUX_2.oidf,
 electron.AUX_2.oidl,
 electron.AUX_2.oidr,
 electron.AUX_2.obse
FROM electron.AUX_2;


--
-- Crear Y Validar Tabla de Pagos
--
CREATE TABLE TMP_CUENTAS
SELECT A.documento_id AS ced, A.credito_id AS ncont, t_lista_cobros.documento_id AS _ced
FROM t_lista_cobros AS A
JOIN t_lista_cobros ON t_lista_cobros.credito_id = A.credito_id
AND t_lista_cobros.documento_id != A.documento_id
GROUP BY t_lista_cobros.documento_id;

--
-- Ver las Diferencias
--
SELECT *
FROM `TMP_CUENTAS`
JOIN t_clientes_creditos ON t_clientes_creditos.contrato_id = TMP_CUENTAS.ncont
AND t_clientes_creditos.documento_id != TMP_CUENTAS.ced;

--
-- Eliminar Relaciones Faltas
--

DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 11960905 AND `t_lista_cobros`.`credito_id` = '009724';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 9263925 AND `t_lista_cobros`.`credito_id` = 'A006085';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 17321024 AND `t_lista_cobros`.`credito_id` = '4273';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 11220645 AND `t_lista_cobros`.`credito_id` = '011322';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 8136381 AND `t_lista_cobros`.`credito_id` = '3733';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 15032917 AND `t_lista_cobros`.`credito_id` = '4746';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 8031815 AND `t_lista_cobros`.`credito_id` = '011851';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 10714184 AND `t_lista_cobros`.`credito_id` = '5367';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 13229102 AND `t_lista_cobros`.`credito_id` = '5763';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 11960930 AND `t_lista_cobros`.`credito_id` = '007485';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 14107003 AND `t_lista_cobros`.`credito_id` = '3983';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 3510571 AND `t_lista_cobros`.`credito_id` = '005613';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 9763043 AND `t_lista_cobros`.`credito_id` = '005608';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`credito_id` = '006401';
DELETE FROM `electron`.`t_lista_cobros` WHERE `t_lista_cobros`.`documento_id` = 14107003 AND `t_lista_cobros`.`credito_id` = '2171';

--
-- Crear t_pagos Agregar Indice
--
INSERT INTO grupo.t_pago (ced, oid,fech,mont,dsc,obse,crea) 
SELECT documento_id AS ced, credito_id AS oid, fecha AS fech, monto AS mont, descripcion AS dsc, mes AS obse, modificado  AS crea  
FROM electron.t_lista_cobros;
