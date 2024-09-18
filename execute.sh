#!/bin/bash
make 
git clone https://github.com/LucasKuhn/minishell_tester.git 
cd minishell_tester
sed -i '19d' redirects
cp ./minishell ./minishell_tester
cp -r ./test ./test_minishell_tester
cd minishell_tester
./tester 
