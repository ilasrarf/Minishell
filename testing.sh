

/tmp // is a dir stat

/dddd //      (is filename contains / pass to execve)

</

^C should not do anything when a command is executing

minishell: (null): command not found // done

cat <<end  stop executin // done

<<end cat>1| <<end cat>2|<<end cat >3 // done

echo "'$USER'"""""'$USER'$USER$US // done

{
	bash-3.2$ .
	bash: .: filename argument required
	.: usage: . filename [arguments]
	bash-3.2$ ..
	bash: ..: command not found
}

{
	bash-3.2$ ""
	bash: : command not found
}

expand ~ to HOME



cat | cat | ls // ctrl c


add exit status to builting's : export cd

