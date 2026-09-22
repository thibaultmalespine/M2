FROM antmicro/renode:latest
USER root
# Install any extra dependencies if needed (e.g. for GUI or tools)
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    git wget curl \
    dotnet-sdk-10.0 \
    python3-venv

# Download renode portable
# RUN mkdir /renode && curl -fsSL https://github.com/renode/renode/releases/download/v1.16.1/renode-1.16.1.linux-portable-dotnet.tar.gz | tar xvfz - -C /renode --strip-components=1
# RUN mkdir -p /opt/renode/bin && curl -fsSL https://github.com/renode/renode/releases/download/v1.16.1/renode-1.16.1.linux-portable.tar.gz | tar xvfz - -C /opt/renode/bin --strip-components=1
# RUN mkdir -p /opt/renode/bin && curl -fsSL https://github.com/renode/renode/releases/download/v1.17.0/renode-1.17.0.linux-portable.tar.gz | tar xvfz - -C /opt/renode/bin --strip-components=1

# Clone RP2040 community support (excellent peripheral coverage)
RUN git clone https://github.com/matgla/Renode_RP2040.git /repos/Renode_RP2040
WORKDIR /repos/Renode_RP2040
RUN ./setup_venv.sh
RUN ./venv/bin/pip install -r "tests/requirements.txt"
RUN ./venv/bin/pip install -r "visualization/requirements.txt"
RUN dotnet build emulation/Peripherals.csproj -c Release
# For RP2350, you can use AntMicro's System Designer scripts or official examples
# (RP2350 support exists in recent Renode versions)

# Optional: Make the repo available by default
ENV RENODE_PATH_ADD="/repos/Renode_RP2040"
# ENV PATH="$PATH:/opt/renode"
ENV VIRTUAL_ENV=/repos/Renode_RP2040/venv
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

CMD ["renode"]
