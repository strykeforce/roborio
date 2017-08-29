#
# roborio utils
#
hostname = 'roborio'

Vagrant.configure('2') do |config|
  config.vm.box = 'ubuntu/trusty64'
  config.vm.hostname = hostname

  config.vm.provider 'virtualbox' do |v|
    v.name = hostname
    v.memory = 2048
    v.cpus = 4
    v.customize ['modifyvm', :id, '--paravirtprovider', 'kvm']
  end

  config.vm.provider 'vmware_fusion' do |v, override|
    override.vm.box = 'bento/ubuntu-16.04'
    v.vmx['memsize'] = '2048'
    v.vmx['numvcpus'] = '4'
  end

  # config.vm.network 'public_network'

  # We provision using ansible_local, bootstrap our ansible roles by
  # downloading them from our repo.
  config.vm.provision 'shell', inline: <<-SCRIPT
  GIT=/usr/bin/git
  ANSIBLE_REPO=https://github.com/strykeforce/ansible.git
  ANSIBLE_VERSION=master
  ANSIBLE_DIR=/opt/ansible

  [[ ! -x $GIT ]] && apt-get install -y git

  [[ ! -d $ANSIBLE_DIR ]] && $GIT clone -q $ANSIBLE_REPO $ANSIBLE_DIR

  cd $ANSIBLE_DIR
  $GIT checkout -q $ANSIBLE_VERSION
  $GIT pull -q
  SCRIPT

  config.vm.provision 'ansible_local' do |ansible|
    ansible.provisioning_path = '/opt/ansible'
    ansible.playbook = 'vagrant.yml'
    ansible.groups = {
      'roborio' => ['default']
    }
    ansible.sudo = true
    ansible.verbose = false
  end
end
