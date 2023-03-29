

# git submodule foreach "
#     # git rm --cached \$sm_path;
#     # rm -rf \$sm_path/.git
#     echo \$sm_path;
# "

all_paths=(
"arras/arras4_core"
"arras/arras_render"
"arras/distributed/arras4_node"
"arras/distributed/minicoord"
"cmake_modules"
"moonray/hydra/hdMoonray"
"moonray/hydra/moonray_sdr_plugins"
"moonray/mcrt_denoise"
"moonray/moonray"
"moonray/moonray_arras/mcrt_computation"
"moonray/moonray_arras/mcrt_dataio"
"moonray/moonray_arras/mcrt_messages"
"moonray/moonray_dcc_plugins"
"moonray/moonray_gui"
"moonray/moonshine"
"moonray/moonshine_usd"
"moonray/render_profile_viewer"
"moonray/scene_rdl2"
)

for p in "${all_paths[@]}"; do
    git rm --cached $p;
    rm -rf $p/.git;
done
