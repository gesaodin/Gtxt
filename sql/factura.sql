--
-- Seleccion Simple
--
INSERT INTO grupo.t_factura (oidp,nfac,mont,crea,oidr,oidl)
SELECT grupo.t_persona.oid, t1.numero_factura, t1.total, t1.fecha_verificado,t1.oid,t1.oidl
FROM grupo.t_persona
JOIN (
SELECT documento_id, numero_factura, SUM( cantidad ) AS total, fecha_verificado, electron.t_ubicacion.oid,grupo.t_banco.oid AS oidl 
FROM electron.t_clientes_creditos
JOIN grupo.t_banco ON grupo.t_banco.nmbr = electron.t_clientes_creditos.cobrado_en
LEFT JOIN electron.t_ubicacion ON electron.t_ubicacion.descripcion = electron.t_clientes_creditos.codigo_n
GROUP BY numero_factura
) AS t1 ON grupo.t_persona.ced = t1.documento_id;