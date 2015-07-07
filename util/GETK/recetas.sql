-- phpMyAdmin SQL Dump
-- version 2.6.1-pl3
-- http://www.phpmyadmin.net
-- 
-- Servidor: localhost
-- Tiempo de generación: 06-04-2005 a las 16:41:03
-- Versión del servidor: 4.0.21
-- Versión de PHP: 5.0.2
-- 
-- Base de datos: `recetas`
-- 

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `control`
-- 

CREATE TABLE `control` (
  `id` int(4) NOT NULL auto_increment,
  `first` int(4) NOT NULL default '0',
  `last` int(4) NOT NULL default '0',
  `done` enum('y','n') NOT NULL default 'n',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM AUTO_INCREMENT=2 ;

-- 
-- Volcar la base de datos para la tabla `control`
-- 

INSERT INTO `control` VALUES (1, 1, 2, 'n');

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `sys`
-- 

CREATE TABLE `sys` (
  `id` varchar(25) NOT NULL default '',
  `strValue` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

-- 
-- Volcar la base de datos para la tabla `sys`
-- 

INSERT INTO `sys` VALUES ('server', 'www.karlosnet.com');
INSERT INTO `sys` VALUES ('port', '80');
INSERT INTO `sys` VALUES ('url', '/General/receta.php?c=%%id%%');
INSERT INTO `sys` VALUES ('HTTP_server', 'proxy.ochoa.es');
INSERT INTO `sys` VALUES ('HTTP_user', 'dvela');
INSERT INTO `sys` VALUES ('HTTP_password', 'deherail23');
INSERT INTO `sys` VALUES ('HTTP_port', '8080');
INSERT INTO `sys` VALUES ('basepath', 'D:\\proyectos\\temp\\pages');
INSERT INTO `sys` VALUES ('HTTP_use_proxy', 'yes');

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `textos`
-- 

CREATE TABLE `textos` (
  `id` int(4) NOT NULL default '0',
  `idJob` int(4) NOT NULL default '0',
  `texto` longtext NOT NULL,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

-- 
-- Volcar la base de datos para la tabla `textos`
-- 

        