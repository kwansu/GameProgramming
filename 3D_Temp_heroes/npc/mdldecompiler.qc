$cd "C:\Users\kwansu\Desktop\npc"
$modelname "npc\ti\npc_ti.mdl"
$model "ti" "npc_ti.smd" {
     flexfile "mdldecompiler_expressions.vta" {
          flex "lid_raiser" frame 5
          flex "lid_tightener" frame 6
          flex "lid_droop" frame 7
          flex "lid_closer" frame 8
          flex "blink" frame 9
          flex "inner_raiser" frame 10
          flex "outer_raiser" frame 11
          flex "lowerer" frame 12
          flex "dilator" frame 13
          flex "cheek_raiser" frame 14
          flex "upper_raiser" frame 15
          flex "corner_puller" frame 16
          flex "conner_depres" frame 17
          flex "chin_raiser" frame 18
          flex "presser" frame 19
          flex "part" frame 20
          flex "pucker" frame 21
          flex "funneler" frame 22
          flex "stretcher" frame 23
          flex "bite" frame 24
          flex "jaw_clencher" frame 25
          flex "jaw_drop" frame 26
          flex "mouth_drop" frame 27
          flex "sneer_left" frame 28
          flex "cheek_puffer" frame 29
          flex "mouth_sideways_left" frame 30
          flex "mouth_sideways_right" frame 31
          flex "lower_lip" frame 32
          flex "lip_bite" frame 33
          flex "jaw_sideways_R" frame 34
          flex "jaw_sideways_L" frame 35
          flex "eyes_left" frame 36
          flex "eyes_right" frame 37
          flex "lip_ahn" frame 38
          flex "lip_oh" frame 39
          flex "lip_oo" frame 40
          flex "worried_open" frame 41
          flex "worried_close" frame 42
          flex "surprised" frame 43
          flex "smile" frame 44
          flex "cry" frame 45
          flex "talk" frame 46
          flex "talk_wide" frame 47
          flex "talk_narrow" frame 48
     }
     eyeball righteye ValveBiped.Bip01_Head1 -1.116 -2.016 62.045 eyeball_r 1.196  2.500 npc_ti_pupil_r01 0.650
     eyeball lefteye ValveBiped.Bip01_Head1 1.116 -2.016 62.045 eyeball_l 1.196  -2.500 npc_ti_pupil_l01 0.650
     // If you uncomment the following lines the eyes will be closed
     // I'm including it anyway in case anyone wants to experiment
     // eyelid  upper_right "mdldecompiler_expressions.vta" lowerer 4 0.000000 neutral 4 0.000000 raiser 4 0.000000 split 0.1 eyeball righteye
     // eyelid  lower_right "mdldecompiler_expressions.vta" lowerer 4 0.000000 neutral 4 0.000000 raiser 4 0.000000  split 0.1 eyeball righteye
     // If you uncomment the following lines the eyes will be closed
     // I'm including it anyway in case anyone wants to experiment
     // eyelid  upper_left "mdldecompiler_expressions.vta" lowerer 4 0.000000 neutral 4 0.000000 raiser 4 0.000000 split -0.1 eyeball lefteye
     // eyelid  lower_left "mdldecompiler_expressions.vta" lowerer 4 0.000000 neutral 4 0.000000 raiser 4 0.000000  split -0.1 eyeball lefteye
     mouth 0 "mouth"  ValveBiped.Bip01_Head1 0.000 1.000 0.000
     flexcontroller eyelid lid_raiser "range" 0.000 1.000
     flexcontroller eyelid lid_tightener "range" 0.000 1.000
     flexcontroller eyelid lid_droop "range" 0.000 1.000
     flexcontroller eyelid lid_closer "range" 0.000 1.000
     flexcontroller eyelid blink "range" 0.000 1.000
     flexcontroller brow inner_raiser "range" 0.000 1.000
     flexcontroller brow outer_raiser "range" 0.000 1.000
     flexcontroller brow lowerer "range" 0.000 1.000
     flexcontroller nose dilator "range" 0.000 1.000
     flexcontroller mouth cheek_raiser "range" 0.000 1.000
     flexcontroller a upper_raiser "range" 0.000 1.000
     flexcontroller a corner_puller "range" 0.000 1.000
     flexcontroller a conner_depres "range" 0.000 1.000
     flexcontroller a chin_raiser "range" 0.000 1.000
     flexcontroller a presser "range" 0.000 1.000
     flexcontroller a part "range" 0.000 1.000
     flexcontroller a pucker "range" 0.000 1.000
     flexcontroller a funneler "range" 0.000 1.000
     flexcontroller a stretcher "range" 0.000 1.000
     flexcontroller a bite "range" 0.000 1.000
     flexcontroller a jaw_clencher "range" 0.000 1.000
     flexcontroller a jaw_drop "range" 0.000 1.000
     flexcontroller a mouth_drop "range" 0.000 1.000
     flexcontroller a sneer_left "range" 0.000 1.000
     flexcontroller a cheek_puffer "range" 0.000 1.000
     flexcontroller a mouth_sideways_left "range" 0.000 1.000
     flexcontroller a mouth_sideways_right "range" 0.000 1.000
     flexcontroller a lower_lip "range" 0.000 1.000
     flexcontroller a lip_bite "range" 0.000 1.000
     flexcontroller a jaw_sideways_R "range" 0.000 1.000
     flexcontroller a jaw_sideways_L "range" 0.000 1.000
     flexcontroller eyes eyes_updown "range" -20.000 20.000
     flexcontroller eyes eyes_rightleft "range" -30.000 30.000
     flexcontroller eyes eyes_left "range" 0.000 1.000
     flexcontroller eyes eyes_right "range" 0.000 1.000
     flexcontroller a lip_ahn "range" 0.000 1.000
     flexcontroller a lip_oh "range" 0.000 1.000
     flexcontroller a lip_oo "range" 0.000 1.000
     flexcontroller eyes worried_open "range" 0.000 1.000
     flexcontroller eyes worried_close "range" 0.000 1.000
     flexcontroller eyes surprised "range" 0.000 1.000
     flexcontroller eyes smile "range" 0.000 1.000
     flexcontroller eyes cry "range" 0.000 1.000
     flexcontroller eyes talk "range" 0.000 1.000
     flexcontroller eyes talk_wide "range" 0.000 1.000
     flexcontroller eyes talk_narrow "range" 0.000 1.000
    %lid_raiser =  lid_raiser
    %lid_tightener =  lid_tightener
    %lid_droop =  lid_droop
    %lid_closer =  lid_closer
    %blink =  blink
    %inner_raiser =  inner_raiser
    %outer_raiser =  outer_raiser
    %lowerer =  lowerer
    %dilator =  dilator
    %cheek_raiser =  cheek_raiser
    %upper_raiser =  upper_raiser
    %corner_puller =  corner_puller
    %conner_depres =  conner_depres
    %chin_raiser =  chin_raiser
    %presser =  presser
    %part =  part
    %pucker =  pucker
    %funneler =  funneler
    %stretcher =  stretcher
    %bite =  bite
    %jaw_clencher =  jaw_clencher
    %jaw_drop =  jaw_drop
    %mouth_drop =  mouth_drop
    %sneer_left =  sneer_left
    %cheek_puffer =  cheek_puffer
    %mouth_sideways_left =  mouth_sideways_left
    %mouth_sideways_right =  mouth_sideways_right
    %lower_lip =  lower_lip
    %lip_bite =  lip_bite
    %jaw_sideways_R =  jaw_sideways_R
    %jaw_sideways_L =  jaw_sideways_L
    %eyes_updown =  eyes_updown
    %eyes_rightleft =  eyes_rightleft
    %eyes_left =  eyes_left
    %eyes_right =  eyes_right
    %lid_tightener =  lid_tightener
    %lid_droop =  lid_droop
    %lid_closer =  lid_closer
    %blink =  blink
    %inner_raiser =  inner_raiser
    %outer_raiser =  outer_raiser
    %lip_ahn =  lip_ahn
    %lip_oh =  lip_oh
    %lip_oo =  lip_oo
    %worried_open =  worried_open
    %worried_close =  worried_close
    %surprised =  surprised
    %smile =  smile
    %cry =  cry
    %talk =  talk
    %talk_wide =  talk_wide
    %talk_narrow =  talk_narrow
}
$poseparameter body_yaw -35.00 35.00
$poseparameter body_pitch -41.50 59.00
$poseparameter body_roll -40.00 40.00
$poseparameter spine_yaw -35.00 35.00
$poseparameter spine_pitch -41.50 59.00
$poseparameter spine_roll -40.00 40.00
$poseparameter head_yaw -39.60 39.60
$poseparameter head_pitch -40.00 20.00
$poseparameter head_roll -19.82 19.82
$poseparameter Larm_yaw -10.37 30.28
$poseparameter Larm_pitch -18.35 15.88
$poseparameter Larm_roll -10.37 30.28
$cdmaterials "models\npc\ti\"
$texturegroup skinfamilies
{
	{"npc_ti_hair.vmt"
 "npc_ti_cloth01.vmt"
 "npc_ti_cloth02.vmt"
 "npc_ti_skin_face.vmt"
 "npc_ti_teeth.vmt"
 "npc_ti_eyelash.vmt"
 "npc_ti_skin_body.vmt"
 "npc_ti_eyeball_l.vmt"
 "npc_ti_eyeball_r.vmt"
}
 	{"npc_ti_hair.vmt"
 "npc_ti_cloth01.vmt"
 "npc_ti_cloth02.vmt"
 "npc_ti_skin_face02.vmt"
 "npc_ti_teeth.vmt"
 "npc_ti_eyelash.vmt"
 "npc_ti_skin_body.vmt"
 "npc_ti_eyeball_l.vmt"
 "npc_ti_eyeball_r.vmt"
}
 }
$hboxset "default"
$hbox 3 "ValveBiped.Bip01_Pelvis" -3.500  -4.000  -6.000  3.500  4.000  6.000
$hbox 3 "ValveBiped.Bip01_Spine1" -2.500  -3.000  -4.500  2.500  3.000  4.500
$hbox 2 "ValveBiped.Bip01_Spine2" -1.000  -4.500  -4.500  8.000  4.500  4.500
$hbox 1 "ValveBiped.Bip01_Neck1" 1.000  -1.500  -1.500  3.000  2.500  1.500
$hbox 1 "ValveBiped.Bip01_Head1" 1.000  -4.500  -3.500  8.000  4.500  3.500
$hbox 5 "ValveBiped.Bip01_R_UpperArm" -0.500  -1.500  -2.000  9.500  1.500  1.000
$hbox 5 "ValveBiped.Bip01_R_Forearm" -0.500  -1.500  -1.000  9.500  1.500  2.000
$hbox 5 "ValveBiped.Bip01_R_Hand" 0.250  -0.500  -3.000  6.750  1.500  3.000
$hbox 4 "ValveBiped.Bip01_L_UpperArm" -0.500  -1.500  -1.000  9.500  1.500  2.000
$hbox 4 "ValveBiped.Bip01_L_Forearm" -0.500  -1.500  -1.500  9.500  1.500  1.500
$hbox 4 "ValveBiped.Bip01_L_Hand" 0.250  -1.000  -3.000  6.750  1.000  3.000
$hbox 7 "ValveBiped.Bip01_R_Thigh" 3.500  -3.500  -2.000  16.500  3.500  3.000
$hbox 7 "ValveBiped.Bip01_R_Calf" -1.000  -3.000  -1.500  17.000  2.000  2.500
$hbox 7 "ValveBiped.Bip01_R_Foot" 1.000  -2.500  -1.500  4.000  6.500  2.500
$hbox 6 "ValveBiped.Bip01_L_Thigh" 3.500  -3.500  -3.000  16.500  3.500  2.000
$hbox 6 "ValveBiped.Bip01_L_Calf" -1.000  -3.000  -2.500  17.000  2.000  1.500
$hbox 6 "ValveBiped.Bip01_L_Foot" 1.000  -2.500  -2.500  4.000  6.500  1.500
// Model uses material "npc_ti_hair.vmt"
// Model uses material "npc_ti_cloth01.vmt"
// Model uses material "npc_ti_cloth02.vmt"
// Model uses material "npc_ti_skin_face.vmt"
// Model uses material "npc_ti_teeth.vmt"
// Model uses material "npc_ti_eyelash.vmt"
// Model uses material "npc_ti_skin_body.vmt"
// Model uses material "npc_ti_eyeball_l.vmt"
// Model uses material "npc_ti_eyeball_r.vmt"
// Model uses material "npc_ti_hair02.vmt"
// Model uses material "npc_ti_cloth03.vmt"
// Model uses material "npc_ti_cloth05.vmt"
// Model uses material "npc_ti_pupil_r01.vmt"
// Model uses material "glint.vmt"
// Model uses material "npc_ti_pupil_l01.vmt"
// Model uses material "npc_ti_skin_face_tears01.vmt"
// Model uses material "npc_ti_skin_face02.vmt"
// Model uses material "npc_ti_skin_face_tears02.vmt"
$attachment "eyes" "ValveBiped.Bip01_Head1" 3.65 3.59 -0.00 rotate -0.00 82.41 90.00
$attachment "lefteye" "ValveBiped.Bip01_Head1" 3.61 3.60 1.12 rotate -0.00 82.41 90.00
$attachment "righteye" "ValveBiped.Bip01_Head1" 3.61 3.60 -1.12 rotate -0.00 82.41 90.00
$attachment "forward" "ValveBiped.Bip01_Head1" 0.00 0.00 0.00 rotate -0.00 90.00 90.00
$attachment "Anim_Attachment_RH" "ValveBiped.Anim_Attachment_RH" -0.00 -0.00 -0.00 rotate -0.00 0.00 -0.00
$attachment "anim_attachment_CAM" "ValveBiped.Anim_Attachment_CAM" -0.00 -0.00 -0.00 rotate 0.00 -0.00 0.00
$attachment "ceiling" "ValveBiped.Bip01_Head1" 50.00 -0.00 -0.00 rotate 0.00 -0.00 0.00
$includemodel "npc\ti\_anim\ti_actor_motion.mdl"
$includemodel "npc\ti\_anim\ti_common_motion.mdl"
$surfaceprop "flesh"
$eyeposition -0.000 0.000 62.000
$illumposition -2.295 0.175 33.707
$sequence ragdoll "ragdoll" ACT_DIERAGDOLL -1 fps 1.00
$animation mdldecompiler_delta.smd "mdldecompiler_delta.smd" fps 30
$animation a_body_rot_z_lt "a_body_rot_z_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_body_rot "a_body_rot" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_body_rot_z_rt "a_body_rot_z_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence body_rot_z "a_body_rot_z_lt" fps 30.00 {
  blendwidth 3
  blend body_yaw -34.999966 34.999966
  delta
  autoplay
 a_body_rot a_body_rot_z_rt
}
$animation a_spine_rot_dwn "a_spine_rot_dwn" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_spine_rot "a_spine_rot" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_spine_rot_up "a_spine_rot_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence body_rot_y "a_spine_rot_dwn" fps 30.00 {
  blendwidth 3
  blend body_pitch -41.499939 58.999901
  delta
  autoplay
 a_spine_rot a_spine_rot_up
}
$animation a_spine_rot_lt "a_spine_rot_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_spine_rot_rt "a_spine_rot_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence body_rot_x "a_spine_rot_lt" fps 30.00 {
  blendwidth 3
  blend body_roll -39.999981 39.999985
  delta
  autoplay
 a_spine_rot a_spine_rot_rt
}
$animation a_spine_rot_z_lt "a_spine_rot_z_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_spine_rot_z_rt "a_spine_rot_z_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence spine_rot_z "a_spine_rot_z_lt" fps 30.00 {
  blendwidth 3
  blend spine_yaw -34.999966 34.999966
  delta
  autoplay
 a_spine_rot a_spine_rot_z_rt
}
$sequence spine_rot_y "a_spine_rot_dwn" fps 30.00 {
  blendwidth 3
  blend spine_pitch -41.499939 58.999901
  delta
  autoplay
 a_spine_rot a_spine_rot_up
}
$sequence spine_rot_x "a_spine_rot_lt" fps 30.00 {
  blendwidth 3
  blend spine_roll -39.999981 39.999985
  delta
  autoplay
 a_spine_rot a_spine_rot_rt
}
$animation a_head_rot_z_lt "a_head_rot_z_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_head_rot "a_head_rot" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_head_rot_z_rt "a_head_rot_z_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence head_rot_z "a_head_rot_z_lt" fps 30.00 {
  blendwidth 3
  blend head_yaw -39.602013 39.602020
  delta
  autoplay
 a_head_rot a_head_rot_z_rt
}
$animation a_head_rot_dwn "a_head_rot_dwn" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_head_rot_up "a_head_rot_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence head_rot_y "a_head_rot_dwn" fps 30.00 {
  blendwidth 3
  blend head_pitch -39.999950 19.999977
  delta
  autoplay
 a_head_rot a_head_rot_up
}
$animation a_head_rot_lt "a_head_rot_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_head_rot_rt "a_head_rot_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence head_rot_x "a_head_rot_lt" fps 30.00 {
  blendwidth 3
  blend head_roll -19.817898 19.817917
  delta
  autoplay
 a_head_rot a_head_rot_rt
}
$animation a_Larm_rot_lt "a_Larm_rot_lt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_Larm_rot "a_Larm_rot" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_Larm_rot_rt "a_Larm_rot_rt" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence a_Larm_rot_z "a_Larm_rot_lt" fps 30.00 {
  blendwidth 3
  blend Larm_yaw -10.370584 30.277828
  delta
  autoplay
 a_Larm_rot a_Larm_rot_rt
}
$animation a_Larm_rot_dwn "a_Larm_rot_dwn" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_Larm_rot_up "a_Larm_rot_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence a_Larm_rot_y "a_Larm_rot_dwn" fps 30.00 {
  blendwidth 3
  blend Larm_pitch -18.349993 15.882280
  delta
  autoplay
 a_Larm_rot a_Larm_rot_up
}
$sequence a_Larm_rot_x "a_Larm_rot_lt" fps 30.00 {
  blendwidth 3
  blend Larm_roll -10.370584 30.277828
  delta
  autoplay
 a_Larm_rot a_Larm_rot_rt
}
$ikchain rhand ValveBiped.Bip01_R_Hand knee  0.707 0.707 0.000
$ikchain lhand ValveBiped.Bip01_L_Hand knee  0.707 0.707 0.000
$ikchain rfoot ValveBiped.Bip01_R_Foot knee  0.000 1.000 0.000
$ikchain lfoot ValveBiped.Bip01_L_Foot knee  0.000 1.000 0.000
$collisionjoints "phymodel.smd" {

	$mass 1.0
	$inertia 1.00
	$damping 0.00
	$rotdamping 0.00
	$rootbone "proptibiped.bip01 pelvis"

	$jointconstrain "proptibiped.bip01 spine" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r thigh" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r thigh" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r thigh" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r calf" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r calf" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r calf" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l thigh" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l thigh" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l thigh" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l calf" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l calf" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l calf" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l foot" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foot" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foot" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l toe0" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l toe0" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l toe0" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 spine1" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine1" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine1" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 spine2" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine2" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 spine2" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 neck" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 neck" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 neck" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r clavicle" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r clavicle" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r clavicle" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r upperarm" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r upperarm" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r upperarm" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r forearm" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r forearm" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r forearm" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r hand" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r hand" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r hand" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger3" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger3" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger3" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger31" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger31" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger31" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger32" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger32" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger32" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger2" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger2" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger2" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger21" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger21" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger21" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger22" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger22" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger22" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger1" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger1" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger1" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger11" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger11" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger11" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger12" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger12" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger12" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger0" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger0" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger0" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger02" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger02" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger02" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger4" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger4" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger4" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r foretwist" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foretwist" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foretwist" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger41" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger41" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger41" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r finger42" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger42" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r finger42" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l clavicle" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l clavicle" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l clavicle" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l upperarm" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l upperarm" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l upperarm" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01_l_shoulder01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_l_shoulder01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_l_shoulder01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01_l_upperarm01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_l_upperarm01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_l_upperarm01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l forearm" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l forearm" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l forearm" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l hand" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l hand" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l hand" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger4" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger4" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger4" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger3" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger3" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger3" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger31" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger31" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger31" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger32" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger32" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger32" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger2" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger2" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger2" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger21" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger21" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger21" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger22" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger22" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger22" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger1" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger1" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger1" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger11" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger11" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger11" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger12" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger12" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger12" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger0" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger0" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger0" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger02" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger02" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger02" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger41" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger41" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger41" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l foretwist" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foretwist" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foretwist" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l finger42" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger42" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l finger42" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01_r_shoulder01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_r_shoulder01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_r_shoulder01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01_r_upperarm01" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_r_upperarm01" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01_r_upperarm01" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r foretwist1" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foretwist1" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foretwist1" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 head" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 head" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 head" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 l foretwist1" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foretwist1" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 l foretwist1" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r foot" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foot" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r foot" z limit 0.00 0.00 0.00

	$jointconstrain "proptibiped.bip01 r toe0" x limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r toe0" y limit 0.00 0.00 0.00
	$jointconstrain "proptibiped.bip01 r toe0" z limit 0.00 0.00 0.00
}
