$cd "C:\Users\kwansu\Desktop\bow_wooden\motion"
$modelname "weapon\_monster\bow\bow_woodenelf_warrior.mdl"
$model "studio" "bow_woodenelf_warrior_lift.smd"
$model "studio" "bow_woodenelf_warrior.smd"
$cdmaterials "models\weapon\_monster\bow\"
$hboxset "default"
$hbox 0 "ValveBiped.Anim_Attachment_RH" -37.437  -2.737  -6.454  37.437  2.261  11.015
$hbox 0 "bow1" -13.782  -12.775  -2.261  5.725  37.353  2.737
$hbox 0 "bow2" 0.000  -10.713  -2.261  38.029  1.088  2.737
$hbox 0 "bow3" 0.000  -1.040  -2.261  38.217  10.570  2.737
$hbox 0 "ValveBiped.Bip01_Neck1" -2.025  -1.373  -2.067  0.000  0.000  0.000
// Model uses material "bow_woodenelf_warrior.vmt"
$attachment "anim_attachment" "ValveBiped.Anim_Attachment_RH" 17.64 0.00 -0.00 rotate -0.00 0.00 0.00
$surfaceprop "weapon"
 	"mdlkeyvalue" 	{ 		"prop_data" 		{ 			"base"		"Wooden.Large" 			"physicsmode"		"1" 			"liftable_type"		"2" 		} 	} 
$illumposition 2.503 5.972 14.902
$sequence idle "idle" ACT_VM_IDLE 1 fps 60.00
$sequence woodenelf_attack_bowshot "woodenelf_attack_bowshot" fps 60.00
$sequence woodenelf_attack_bowshot_begin "woodenelf_attack_bowshot_begin" fps 60.00
$sequence woodenelf_attack_bowshot_during "woodenelf_attack_bowshot_during" fps 60.00
$sequence woodenelf_attack_bowshot_during2 "woodenelf_attack_bowshot_during2" fps 60.00
$sequence woodenelf_attack_bowshot_end "woodenelf_attack_bowshot_end" fps 60.00
$collisionmodel "phymodel.smd" {

	$concave
	$mass 109.8
	$inertia 1.00
	$damping 0.00
	$rotdamping 0.00
}
