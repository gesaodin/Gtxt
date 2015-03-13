-- phpMyAdmin SQL Dump
-- version 3.5.7
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 22-04-2013 a las 05:27:52
-- Versión del servidor: 5.5.29
-- Versión de PHP: 5.3.14

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `electron`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_control_pagos`
--

CREATE TABLE IF NOT EXISTS `t_control_pagos` (
  `documento_id` int(11) NOT NULL,
  `contrato_id` varchar(32) NOT NULL,
  `fecha_inicio_cobro` date NOT NULL,
  `banco_1` varchar(32) NOT NULL,
  `cuenta_1` varchar(32) NOT NULL,
  `numero_cuotas` tinyint(1) NOT NULL,
  `monto_cuota` decimal(10,0) NOT NULL,
  `monto` double(10,2) DEFAULT NULL,
  `resta` double(10,2) DEFAULT NULL,
  `cobrado_en` varchar(256) NOT NULL,
  `empresa` tinyint(1) NOT NULL,
  `periocidad` tinyint(1) NOT NULL,
  `forma_contrato` tinyint(1) NOT NULL,
  `nomina_procedencia` varchar(255) NOT NULL,
  KEY `documento_id` (`documento_id`),
  KEY `contrato_id` (`contrato_id`),
  KEY `cobrado_en` (`cobrado_en`),
  KEY `empresa` (`empresa`),
  KEY `banco_1` (`banco_1`),
  KEY `nomina_procedencia` (`nomina_procedencia`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cpp_banco`
--

CREATE TABLE IF NOT EXISTS `cpp_banco` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `nmbr` varchar(255) NOT NULL COMMENT 'Nombre',
  `desc` varchar(255) NOT NULL COMMENT 'Descripcion',
  `auto` varchar(255) NOT NULL COMMENT 'Autor',
  `lina` varchar(255) NOT NULL COMMENT 'Linaje del Banco',
  `esta` tinyint(1) NOT NULL COMMENT 'Estaus 1: Creado 2: Procesado',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `proc` datetime NOT NULL COMMENT 'Fecha de Procesado',
  `tama` varchar(255) NOT NULL COMMENT 'Tamano del Archivo',
  `empr` int(2) NOT NULL COMMENT 'Empresa 0: Cooperativa 1: Grupo',
  `mes` varchar(8) NOT NULL COMMENT 'Mes (YYYY-MM)',
  `peri` int(2) NOT NULL COMMENT 'Periodo',
  `fcon` int(2) NOT NULL COMMENT 'Forma del Contrato',
  `fact` varchar(8) NOT NULL COMMENT 'Fecha Actual (Ymd)',
  `nomi` varchar(255) NOT NULL COMMENT 'Nomina Procedencia',
  PRIMARY KEY (`oid`),
  KEY `nmbr` (`nmbr`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;


-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_cargar_txt`
--

CREATE TABLE IF NOT EXISTS `t_cargar_txt` (
  `cedula` int(10) DEFAULT NULL,
  `monto` decimal(10,2) DEFAULT NULL,
  `archivo` varchar(50) DEFAULT NULL,
  `procesada` TINYINT(1) NULL DEFAULT '0',
  KEY `cedula` (`cedula`),
  KEY `archivo` (`archivo`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_txt_leer`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cpp_archivo`
--

CREATE TABLE IF NOT EXISTS `cpp_archivo` (
  `oid` int(11) NOT NULL AUTO_INCREMENT,
  `nmbr` varchar(255) NOT NULL COMMENT 'Nombre',
  `desc` varchar(255) NOT NULL COMMENT 'Descripcion',
  `auto` varchar(255) NOT NULL COMMENT 'Autor',
  `lina` varchar(255) NOT NULL COMMENT 'Linaje del Banco',
  `esta` tinyint(1) NOT NULL COMMENT 'Estaus 1: Creado 2: Procesado',
  `crea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Creacion Fecha',
  `tama` varchar(255) NOT NULL COMMENT 'Tamano del Archivo',
  PRIMARY KEY (`oid`),
  KEY `nmbr` (`nmbr`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1;



-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_formacontrato`
--

CREATE TABLE IF NOT EXISTS `t_formacontrato` (
  `oid` int(2) NOT NULL COMMENT 'Identificador',
  `nmbr` varchar(128) NOT NULL COMMENT 'Nombre',
  `dscr` varchar(255) NOT NULL COMMENT 'Descripcion',
  KEY `oid` (`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Forma Contrato';

--
-- Volcado de datos para la tabla `t_formacontrato`
--

INSERT INTO `t_formacontrato` (`oid`, `nmbr`, `dscr`) VALUES
(0, 'UNICO', ''),
(1, 'AGUINALDOS - CUOTA ESPECIAL', 'AGUINALDOS'),
(2, 'VACACIONES  - CUOTA ESPECIAL', 'VACACIONES'),
(3, 'CUOTA EXTRAORDINARIA', ''),
(4, 'UNICO EXTRA', ''),
(5, 'ESPECIAL - EXTRA', ''),
(6, '', '');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `t_periodicidad`
--

CREATE TABLE IF NOT EXISTS `t_periodicidad` (
  `oid` int(2) NOT NULL COMMENT 'Identificador',
  `nmbr` varchar(128) NOT NULL COMMENT 'Nombre',
  `dscr` varchar(255) NOT NULL COMMENT 'Descripcion',
  KEY `oid` (`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Diferentes periodos de pagos';

--
-- Volcado de datos para la tabla `t_periodicidad`
--

INSERT INTO `t_periodicidad` (`oid`, `nmbr`, `dscr`) VALUES
(0, 'SEMANAL', ''),
(1, 'CATORCENAL', ''),
(2, 'QUINCENAL 15 - 30', ''),
(3, 'QUINCENAL 10 - 20', ''),
(4, 'MENSUAL', ''),
(5, 'TRIMESTRAL', ''),
(6, 'ANUAL', '');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
