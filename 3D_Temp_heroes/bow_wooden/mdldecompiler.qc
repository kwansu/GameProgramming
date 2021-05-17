$cd "C:\Users\kwansu\Desktop\bow_wooden"
$modelname "monster\woodenelf\woodenelf_brave.mdl"
$model "woodenelf" "woodenelf_warrior.smd"
$lod 15
 {
  replacemodel "woodenelf_warrior" "lod1_woodenelf_warrior"
}
$lod 30
 {
  replacemodel "woodenelf_warrior" "lod2_woodenelf_warrior"
}
$poseparameter body_yaw -35.00 35.00
$poseparameter body_pitch -45.00 80.00
$poseparameter body_roll -40.00 40.00
$poseparameter spine_yaw -35.00 35.00
$poseparameter spine_pitch -45.00 80.00
$poseparameter spine_roll -40.00 40.00
$poseparameter head_yaw -39.60 39.60
$poseparameter head_pitch -40.00 20.00
$poseparameter head_roll -19.82 19.82
$cdmaterials "models\monster\woodenelf\"
$texturegroup skinfamilies
{
	{"woodenelf_warrior02.vmt"
 "woodenelf_warrior.vmt"
}
 	{"woodenelf_warrior02_gray.vmt"
 "woodenelf_warrior_gray.vmt"
}
 	{"woodenelf_warrior02_blue.vmt"
 "woodenelf_warrior_blue.vmt"
}
 	{"woodenelf_warrior02_green.vmt"
 "woodenelf_warrior_green.vmt"
}
 }
$hboxset "default"
$hbox 3 "ValveBiped.Bip01_Pelvis" -5.495  -8.470  -9.758  6.555  8.470  9.758
$hbox 3 "ValveBiped.Bip01_Spine1" -6.236  -8.128  -9.485  4.093  8.128  9.485
$hbox 2 "ValveBiped.Bip01_Spine2" -3.910  -8.607  -10.830  11.890  8.607  10.830
$hbox 1 "ValveBiped.Bip01_Neck1" -0.901  -4.834  -5.438  5.461  5.974  5.438
$hbox 1 "ValveBiped.Bip01_Head1" -0.365  -7.706  -6.213  10.625  7.706  6.213
$hbox 5 "ValveBiped.Bip01_R_UpperArm" -6.179  -5.814  -5.746  16.439  5.814  4.606
$hbox 5 "ValveBiped.Bip01_R_Forearm" -4.400  -5.905  -4.241  14.660  5.905  5.381
$hbox 5 "ValveBiped.Bip01_R_Hand" -1.858  -2.428  -6.088  9.838  3.568  6.088
$hbox 4 "ValveBiped.Bip01_L_UpperArm" -6.965  -5.620  -4.332  17.225  5.620  5.472
$hbox 4 "ValveBiped.Bip01_L_Forearm" -3.956  -5.540  -4.720  14.216  5.540  4.720
$hbox 4 "ValveBiped.Bip01_L_Hand" -2.565  -3.545  -6.179  10.545  3.545  6.179
$hbox 7 "ValveBiped.Bip01_R_Thigh" 1.151  -8.174  -5.130  21.649  8.174  6.270
$hbox 7 "ValveBiped.Bip01_R_Calf" -3.443  -7.775  -4.457  21.694  6.635  5.597
$hbox 7 "ValveBiped.Bip01_R_Foot" -1.881  -6.236  -2.953  7.581  10.796  4.093
$hbox 6 "ValveBiped.Bip01_L_Thigh" 1.414  -7.387  -6.612  21.386  7.387  5.472
$hbox 6 "ValveBiped.Bip01_L_Calf" -2.907  -7.513  -5.974  21.147  6.373  4.834
$hbox 6 "ValveBiped.Bip01_L_Foot" -1.448  -6.760  -4.286  7.148  11.320  3.146
// Model uses material "woodenelf_warrior02.vmt"
// Model uses material "woodenelf_warrior.vmt"
// Model uses material "woodenelf_warrior_gray.vmt"
// Model uses material "woodenelf_warrior02_gray.vmt"
// Model uses material "woodenelf_warrior_blue.vmt"
// Model uses material "woodenelf_warrior02_blue.vmt"
// Model uses material "woodenelf_warrior_green.vmt"
// Model uses material "woodenelf_warrior02_green.vmt"
$attachment "eyes" "ValveBiped.Bip01_Head1" -18.46 5.22 -0.00 rotate -0.00 82.41 90.00
$attachment "forward" "ValveBiped.Bip01_Head1" 0.00 -0.00 0.00 rotate 0.00 80.00 90.00
$attachment "chest" "ValveBiped.Bip01_Spine2" 0.00 0.00 -0.00 rotate 0.00 90.00 90.00
$attachment "anim_attachment_RH" "ValveBiped.Anim_Attachment_RH" 0.00 -0.00 -0.00 rotate -90.00 90.00 0.00
$attachment "anim_attachment_LH" "ValveBiped.Anim_Attachment_LH" 0.00 -0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "anim_attachment_head" "ValveBiped.Bip01_Head1" 0.00 -0.00 0.00 rotate -90.00 -90.00 0.00
$attachment "ATTACK_POINT_START_00" "ValveBiped.Bip01_Neck1" -0.00 0.00 0.00 rotate 0.00 90.00 90.00
$attachment "ATTACK_POINT_END_00" "ValveBiped.Bip01_Head1" 0.00 -0.00 0.00 rotate 0.00 90.00 90.00
$attachment "throw" "throw" 0.00 -0.00 -0.00 rotate 0.00 -0.00 -0.00
$attachment "arrow_zacco" "ValveBiped.Anim_Attachment_LH" 7.39 -9.03 4.75 rotate -2.00 -36.00 108.00
$attachment "EYE_L" "EYE_glow_L" 0.00 0.00 -0.00 rotate -0.00 -0.00 0.00
$attachment "EYE_R" "EYE_glow_R" 0.00 0.00 -0.00 rotate -0.00 -0.00 0.00
$includemodel "monster\woodenelf\_anim\_woodenelf_attack_motion.mdl"
$includemodel "monster\woodenelf\_anim\_woodenelf_common_motion.mdl"
$includemodel "monster\woodenelf\_anim\_woodenelf_downknee_motion.mdl"
$surfaceprop "flesh"
 	"mdlkeyvalue" 	{ 		"camera_tar