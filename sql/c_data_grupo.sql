-- phpMyAdmin SQL Dump
-- version 3.5.7
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 13-04-2013 a las 09:33:51
-- Versión del servidor: 5.5.29
-- Versión de PHP: 5.3.14

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `grupo`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_abono`
--

CREATE TABLE IF NOT EXISTS `t_abono` (
  `oid` varchar(32) NOT NULL COMMENT 'Numero de Contrato',
  `mont` decimal(10,2) NOT NULL COMMENT 'Monto Total Por Contrato',
  PRIMARY KEY (`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Lista De Abonos';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_banco`
--

CREATE TABLE IF NOT EXISTS `t_banco` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `nmbr` varchar(64) NOT NULL COMMENT 'Nombre',
  `desc` varchar(128) NOT NULL COMMENT 'Descripcion',
  `esta` tinyint(1) NOT NULL COMMENT 'Estaus 1: Activo 2: Inactivo',
  PRIMARY KEY (`oid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 COMMENT='Lista De Bancos';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_contrato`
--

CREATE TABLE IF NOT EXISTS `t_contrato` (
  `ncon` varchar(32) NOT NULL COMMENT 'Numero de Contrato',
  `soli` date NOT NULL COMMENT 'Fecha de Solicitud',
  `icob` date NOT NULL COMMENT 'Fecha de Inicio de Cobro',
  `motv` int(11) NOT NULL COMMENT 'Motivo Deposito, Cheque, Transferencia',
  `cond` int(11) NOT NULL COMMENT 'Codicion Credito, Financiamiento',
  `tipo` int(11) NOT NULL COMMENT 'Forma de Pago Domiciliado, Voucher',
  `form` int(11) NOT NULL COMMENT 'Tipo Aguinaldos, Vacaciones, Unico',
  `peri` int(11) NOT NULL COMMENT 'Periodo Mensual, Quincenal, Anual',
  `empr` int(11) NOT NULL COMMENT 'Empresas Cooperativa Grupo',
  `ncuo` int(11) NOT NULL COMMENT 'Numero de Cuotas',
  `mcuo` decimal(10,2) NOT NULL COMMENT 'Monto Por Cuota',
  `cant` decimal(10,2) NOT NULL COMMENT 'Cantidad del Contrato',
  `mont` decimal(10,2) NOT NULL COMMENT 'Total del Contrato',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `oidn` int(11) NOT NULL COMMENT 'Referencia Nomina Clave Foranea',
  `oidf` int(11) NOT NULL COMMENT 'Referecia Factura Clave Foranea',
  `oidl` int(11) NOT NULL COMMENT 'Referencia Linaje Banco  Clave Foranea',
  `oidr` int(11) NOT NULL COMMENT 'Identificador Responsable',
  `obse` text NOT NULL COMMENT 'Numero de Cuotas',
  UNIQUE KEY `ncon` (`ncon`),
  INDEX `soli` (`soli`),
  INDEX `icob` (`icob`),
  INDEX `oidn` (`oidn`),
  INDEX `oidl` (`oidl`),
  INDEX `oidf` (`oidf`),
  INDEX `oidr` (`oidr`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 COMMENT='Objeto Contratos'
PARTITION BY RANGE (YEAR(soli))(
	PARTITION t_contrato_p1 VALUES LESS THAN(2011),
	PARTITION t_contrato_p2 VALUES LESS THAN(2012),
	PARTITION t_contrato_p3 VALUES LESS THAN(2013),
	PARTITION t_contrato_p4 VALUES LESS THAN(2014)
);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_factura`
--

CREATE TABLE IF NOT EXISTS `t_factura` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `oidp` int(11) NOT NULL COMMENT 'Identificador Persona',
  `nfac` varchar(12) NOT NULL COMMENT 'Numero de Factura',
  `mont` decimal(10,2) NOT NULL COMMENT 'Monto',
  `rest` decimal(10,2) NOT NULL COMMENT 'Resta',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `oidr` int(11) NOT NULL COMMENT 'Identificador del Responsable',
  `oidl` int(11) NOT NULL COMMENT 'Identificador del Banco o Linaje',
  PRIMARY KEY (`oid`),
  KEY `oidp` (`oidp`),
  KEY `oidl` (`oidl`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 COMMENT='Objeto Facturas';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_nomina`
--

CREATE TABLE IF NOT EXISTS `t_nomina` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `nmbr` varchar(128) NOT NULL COMMENT 'Nombre',
  `desc` varchar(255) NOT NULL COMMENT 'Descripcion',
  `esta` bigint(1) NOT NULL COMMENT 'Estaus 1: Activo 2: Inactivo',
  PRIMARY KEY (`oid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_pago`
--

CREATE TABLE IF NOT EXISTS `t_pago` (
  `ced` int(11) NOT NULL,
  `oid` varchar(32) NOT NULL,
  `fech` date DEFAULT NULL,
  `mont` decimal(10,2) NOT NULL,
  `dsc` varchar(255) NOT NULL,
  `obse` varchar(255) NOT NULL,
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  KEY `oid` (`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1
PARTITION BY RANGE (UNIX_TIMESTAMP(crea))(
	PARTITION t_pago_p1 VALUES LESS THAN(UNIX_TIMESTAMP('2010-12-31 00:00:00')),
	PARTITION t_pago_p2 VALUES LESS THAN(UNIX_TIMESTAMP('2011-12-31 00:00:00')),
	PARTITION t_pago_p3 VALUES LESS THAN(UNIX_TIMESTAMP('2012-12-31 00:00:00')),
	PARTITION t_pago_p4 VALUES LESS THAN(UNIX_TIMESTAMP('2013-12-31 00:00:00')),
	PARTITION t_pago_p5 VALUES LESS THAN(UNIX_TIMESTAMP('2014-12-31 00:00:00'))
);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_persona`
--

CREATE TABLE IF NOT EXISTS `t_persona` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `ced` int(11) NOT NULL COMMENT 'Cedula de Identidad',
  `pnmb` varchar(64) NOT NULL COMMENT 'Primer Nombre',
  `snmb` varchar(64) NOT NULL COMMENT 'Segundo Nombre',
  `pape` varchar(64) NOT NULL COMMENT 'Primer Apellido',
  `sape` varchar(64) NOT NULL COMMENT 'Segundo Apellido',
  `fnac` date NOT NULL COMMENT 'Fecha Nacimiento',
  `sexo` bit(1) NOT NULL COMMENT 'Identificacion del Sexo',
  `tele` varchar(32) NOT NULL COMMENT 'Telefono',
  `celu` varchar(32) NOT NULL COMMENT 'Celular',
  `obse` varchar(128) NOT NULL COMMENT 'Observaciones Detallatas',
  `zpos` varchar(32) NOT NULL COMMENT 'Codigo Zona Postal',
  `muni` varchar(32) NOT NULL COMMENT 'Municipio',
  `parr` varchar(32) NOT NULL COMMENT 'Sector',
  `sect` varchar(32) NOT NULL COMMENT 'Parroquia',
  `aven` varchar(32) NOT NULL COMMENT 'Avenida',
  `urba` varchar(32) NOT NULL COMMENT 'Urbanizacion',
  `cal` varchar(32) NOT NULL COMMENT 'Identificacion Calle  Numero',
  `rif` varchar(12) NOT NULL COMMENT 'Registro de Informacion Fiscal',
  PRIMARY KEY (`oid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 COMMENT='Objeto Personas';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_usuario`
--

CREATE TABLE IF NOT EXISTS `t_usuario` (
  `oid` int(2) NOT NULL COMMENT 'Identificador Usuario',
  `ced` int(11) NOT NULL COMMENT 'Cedula de Identidad',
  `desc` char(64) NOT NULL COMMENT 'Nombre Completo',
  `seud` char(32) NOT NULL COMMENT 'Seudonimo',
  `clav` char(64) NOT NULL COMMENT 'Clave MD5',
  `corr` char(64) NOT NULL COMMENT 'Correo Electronico',
  `fech` datetime NOT NULL COMMENT 'Fecha Creacion',
  `esta` tinyint(1) NOT NULL COMMENT 'Estatus De Actividad',
  `cone` tinyint(1) NOT NULL COMMENT 'Conectado Al Sistema',
  PRIMARY KEY (`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `_r_personabanco`
--

CREATE TABLE IF NOT EXISTS `_r_personabanco` (
  `oidp` int(11) NOT NULL COMMENT 'Identificador Persona',
  `oidb` int(11) NOT NULL COMMENT 'Identificador Banco',
  `cuenta` varchar(20) NOT NULL COMMENT 'Cuenta Bancaria 20 Digitos',
  `tipo` int(1) NOT NULL COMMENT '1: Nomina 2: Ahorro 3: Corriente',
  KEY `_r_personabanco_ibfk_1` (`oidp`),
  KEY `_r_personabanco_ibfk_2` (`oidb`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Relación Una Persona Muchas Cuentas Bancarias';

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `t_contrato`
--
--ALTER TABLE `t_contrato`
--  ADD CONSTRAINT `t_contrato_ibfk_1` FOREIGN KEY (`oidn`) REFERENCES `t_nomina` (`oid`) ON UPDATE CASCADE,
--  ADD CONSTRAINT `t_contrato_ibfk_2` FOREIGN KEY (`oidl`) REFERENCES `t_banco` (`oid`) ON UPDATE CASCADE,
--  ADD CONSTRAINT `t_contrato_ibfk_3` FOREIGN KEY (`oidf`) REFERENCES `t_factura` (`oid`) ON UPDATE CASCADE,
--  ADD CONSTRAINT `t_contrato_ibfk_4` FOREIGN KEY (`oidr`) REFERENCES `t_usuario` (`oid`) ON UPDATE CASCADE;

--
-- Filtros para la tabla `t_factura`
--
ALTER TABLE `t_factura`
  ADD CONSTRAINT `t_factura_ibfk_1` FOREIGN KEY (`oidp`) REFERENCES `t_persona` (`oid`) ON UPDATE CASCADE,
  ADD CONSTRAINT `t_factura_ibfk_2` FOREIGN KEY (`oidl`) REFERENCES `t_banco` (`oid`) ON UPDATE CASCADE;

--
-- Filtros para la tabla `_r_personabanco`
--
ALTER TABLE `_r_personabanco`
  ADD CONSTRAINT `_r_personabanco_ibfk_1` FOREIGN KEY (`oidp`) REFERENCES `t_persona` (`oid`) ON UPDATE CASCADE,
  ADD CONSTRAINT `_r_personabanco_ibfk_2` FOREIGN KEY (`oidb`) REFERENCES `t_banco` (`oid`) ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;