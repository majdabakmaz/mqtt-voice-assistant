FROM espressif/idf:v3.3.1

WORKDIR /project

ARG PORT
ENV PORT_ENV $PORT

COPY / ./

ENV HOME /tmp

# Start a shell session when the container is run
# CMD echo "========================= To establish serial connection hold BOOT + tap RST ========================="
CMD ["bash"]
# RUN echo $PORT_ENV
#CMD ["idf.py", "build"]

#CMD idf.py build
#CMD idf.py -p $PORT_ENV flash monitor


