$cd "C:\Users\kwansu\Desktop\structure"
$modelname "objects\desert\structure_piecel_c.mdl"
$model "Body" "structure_piecel_c.smd"
$cdmaterials "models\objects\desert\"
$hboxset "default"
$hbox 0 "static_prop" -22.385  -43.225  -64.385  22.385  43.225  64.385
// Model uses material "brick_mixed_drywall_a.vmt"
// Model uses material "brick_mixed_drywall_b.vmt"
$surfaceprop "rock_small"
$illumposition -0.000 0.000 150.000
$sequence idle "idle" fps 1.00
$collisionmodel "phymodel.smd" {

	$concave
	$mass 8080.0
	$inertia 1.00
	$damping 0.00
	$rotdamping 0.00
}
