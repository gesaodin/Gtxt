--
-- Metodo Directo
--
SELECT * FROM t_banco JOIN t_contrato ON t_contrato.oidl = t_banco.oid
WHERE t_banco.oid = 18
AND icob<'2013-04-01' AND form=0 AND tipo!=6


--
-- Metodo Complejo
--

SELECT * FROM t_banco JOIN t_contrato ON t_contrato.oidl = t_banco.oid
JOIN (SELECT oid, sum( mont ) AS mnt FROM t_pago GROUP BY oid) AS t1 ON t1.oid = t_contrato.ncon
WHERE t_banco.oid = 18
AND t_contrato.mont != t1.mnt AND icob<'2013-04-01'
AND form=0 AND tipo!=6

--
-- Metodo Auxiliar
-- Tabla Auxiliar de Creacion
--
TRUNCATE TABLE `t_abono`;
INSERT INTO t_abono (oid,mont) SELECT oid, sum( mont ) AS mnt FROM t_pago GROUP BY oid;
--
-- Luego de la Tabla
--
SELECT ncon,soli,icob,oidf,oidl,oidn,t_contrato.mont,mcuo,ncuo,t_abono.mont AS pago,(t_contrato.mont-t_abono.mont) AS rest 
FROM t_banco JOIN t_contrato ON t_contrato.oidl = t_banco.oid
LEFT JOIN t_abono ON t_abono.oid = t_contrato.ncon
WHERE t_banco.oid = 18
AND t_contrato.mont != t_abono.mont AND icob<'2013-04-01'
AND form=0 AND tipo!=6



