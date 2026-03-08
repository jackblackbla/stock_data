FROM scottyhardy/docker-wine:stable-8.0 AS setup

USER root

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    fluxbox \
    g++-mingw-w64-i686 \
    make \
    locales \
    xvfb \
    && rm -rf /var/lib/apt/lists/*

RUN locale-gen ko_KR.UTF-8 && \
    update-locale LANG=ko_KR.UTF-8 LC_MESSAGES=POSIX

# Initialize the wineuser account and wine prefix during image build.
RUN /usr/bin/entrypoint echo Done
RUN mkdir -p /app /home/wineuser/.wine/drive_c/users/wineuser/AppData/LocalLow && \
    chown -R wineuser:wineuser /app /home/wineuser

WORKDIR /app
USER wineuser

RUN wine cmd.exe /c "echo winesetup complete"

FROM setup AS build

WORKDIR /src
COPY --chown=wineuser:wineuser cpp /src/cpp

RUN cmake -S /src/cpp -B /src/build \
    -DCMAKE_SYSTEM_NAME=Windows \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++ \
    -DCMAKE_RC_COMPILER=i686-w64-mingw32-windres && \
    cmake --build /src/build --config Release -j"$(nproc)"

FROM setup

COPY --from=build /src/build/fetch.exe /app/fetch.exe
COPY --chown=wineuser:wineuser wmca.dll /app/wmca.dll
COPY --chown=wineuser:wineuser bin /app/bin
RUN cp /app/bin/wmca.ini /app/wmca.ini
COPY --chown=wineuser:wineuser docker/fetch-wine/entrypoint.sh /app/entrypoint.sh

ENTRYPOINT ["/app/entrypoint.sh"]
