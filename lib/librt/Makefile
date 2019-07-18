# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 19:33:22 by nihuynh           #+#    #+#              #
#    Updated: 2019/07/18 17:39:46 by sklepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	librt.a
RUNMODE		?=  release
VEC			:=	vec3_add.c vec3_cross.c vec3_mag.c vec3_scalar.c vec3_cos.c \
				vec3_dot.c vec3_normalize.c vec3_sub.c vec3_new.c vec3_print.c \
				vec3_cpy.c vec3_find.c ray_new.c vec3_deflect.c print_matrix.c \
				vec3_matrix_mult.c vec3_matrix_apply.c vec3_refract.c fresnel.c\
				vec3_spherical_cartesian.c ray_offset_origin.c mat_orbit.c	   \
				vec3_mul.c
INTER		:=	inter_cylinder.c inter_plane.c inter_sphere.c inter_cone.c \
				inter_set.c inter_find.c inter_setlight.c inter_setdeflect.c \
				inter_setrefract.c inter_csg.c inter_csg_op.c inter_cube.c \
				inter_tore.c inter_plane_finite.c inter_csg_spe.c
COLOR		:=	color_add.c color_sub.c color_mult.c color_scalar.c \
				colortoi.c color_max.c itocolor.c color_clamp.c color_bool.c \
				color_linear_inter.c
MATRIX		:=	mat3_rot.c mat3.c
NORMAL		:=	normal_cone.c normal_sphere.c normal_cylinder.c normal_plane.c \
				normal_cube.c normal_tore.c
OTHER		:=	uv_mapping.c
SRC			:=	$(VEC) $(INTER) $(COLOR) $(NORMAL) $(MATRIX) $(OTHER)
VPATH		:=	./srcs

# **************************************************************************** #
# Makefile dependency :
include ../libft/mk_c_project.mk
# LIBFT
LIBFT_NAME	:=	libft.a
LIBFT_PATH	:=	../libft
LIB	+=	-L $(LIBFT_PATH) -lft
INC	+=	-I $(LIBFT_PATH)/includes
# **************************************************************************** #
# Target rules :
all: $(NAME)
.PHONY: all

$(NAME): $(OBJ) $(LFT_RULE)
	ar rc $@ $(OBJ) && ranlib $@
	@printf "\033[1;34m$@\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
-include $(DEP)

$(LFT_RULE):
	make -C $(LFT_PATH)/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"

fclean: clean
	$(RM) test.out
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean

norme:
	norminette srcs includes | $(GREP_ERR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: norme
