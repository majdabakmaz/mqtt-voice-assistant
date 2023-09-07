FROM espressif/idf:v5.1.1

WORKDIR /project

ARG PORT
ENV PORT_ENV $PORT


ENV HOME /tmp

# Start a shell session when the container is run
CMD ["bash"]
# RUN echo $PORT_ENV
#CMD ["idf.py", "build"]

#CMD idf.py build
#CMD idf.py -p $PORT_ENV flash monitor