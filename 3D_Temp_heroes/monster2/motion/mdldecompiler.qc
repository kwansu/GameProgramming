$cd "C:\Users\kwansu\Desktop\monster2\motion"
$modelname "weapon/_subweapon/lavasat_breath.mdl"
$model "studio" "lavasat_breath.smd"
$cdmaterials "models\"
$hboxset "default"
$hbox 0 "ValveBiped.Bip01_Head1" 0.000  -3.045  0.000  16.349  0.000  8.414
// Model uses material "error.vmt"
$surfaceprop "ice"
 	"mdlkeyvalue" 	{ 		"prop_data" 		{ 			"base"		"IceRough.Medium" 			"health"		"30" 		} 	} 
$illumposition -4.230 -1.523 8.492
$sequence idle "idle" ACT_VM_IDLE 1 fps 1.00
$collisionmodel "phymodel.smd" {

	$concave
	$mass 137.3
	$inertia 1.00
	$damping 0.00
	$rotdamping 0.00
}
