gcc core/*.c network/*.c threading/*.c ui/*.c \
    -Iheader -Lexternal -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcurl -g 
