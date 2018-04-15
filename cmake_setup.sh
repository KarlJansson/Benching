repo_name="Benching"
repo_name_dbg=$repo_name"_dbg"

cmakemaker

cd ~/Repositories/BuildFiles
rm -rf ./$repo_name
mkdir $repo_name
cd $repo_name
CXX=clang++ cmake ../../$repo_name -DCMAKE_BUILD_TYPE=Release -DCMAKE_USER_MAKE_RULES_OVERRIDE=~/ClangOverrides.txt -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cp compile_commands.json ../../$repo_name

cat <<EOF > ../../$repo_name/.dir-locals.el
((c++-mode (helm-make-build-dir . "../BuildFiles/$repo_name")))
EOF

cd ~/Repositories/BuildFiles
rm -rf ./$repo_name_dbg
mkdir $repo_name_dbg
cd $repo_name_dbg
CXX=clang++ cmake ../../$repo_name -DCMAKE_BUILD_TYPE=Debug -DCMAKE_USER_MAKE_RULES_OVERRIDE=~/ClangOverrides.txt
