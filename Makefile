all:
	make -C src
	make -C libft

fclean:
	make fclean -C src
	make fclean -C libft